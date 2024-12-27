import os, sys, mariadb, threading, argparse
from typing import List, Tuple, LiteralString

parser = argparse.ArgumentParser()
parser.add_argument('-su', '--src-user', default=os.getlogin())
parser.add_argument('-sp', '--src-passwd')
parser.add_argument('-sh', '--src-host', default='localhost')
parser.add_argument('-sd', '--src-db')
parser.add_argument('-sP', '--src-port', default=3306)

parser.add_argument('-du', '--dest-user', default=os.getlogin())
parser.add_argument('-dp', '--dest-passwd')
parser.add_argument('-dh', '--dest-host', default='localhost')
parser.add_argument('-dd', '--dest-db')
parser.add_argument('-dP', '--dest-port', default=3306)
parser.add_argument('-t', '--threads', type=int, default=10)
args = parser.parse_args()

thread_num = min(max(args.threads, 2), 128) // 2
print(thread_num)

source_pool = mariadb.ConnectionPool(
    pool_name='dbcopy_src',
    pool_size=thread_num,
    user=args.src_user,
    passwd=args.src_passwd,
    host=args.src_host,
    db=args.src_db
)

destination_pool = mariadb.ConnectionPool(
    pool_name='dbcopy_dest',
    pool_size=thread_num,
    user=args.dest_user,
    passwd=args.dest_passwd,
    host=args.dest_host,
    db=args.dest_db
)

# Semaphores
source_semaphore = threading.Semaphore(source_pool.pool_size)
destination_semaphore = threading.Semaphore(destination_pool.pool_size)

# Global semaphore to limit total threads
# max_threads = min(source_pool.pool_size, destination_pool.pool_size)
max_threads = source_pool.pool_size + destination_pool.pool_size
thread_limit_semaphore = threading.Semaphore(max_threads)

def show_create(pool: mariadb.ConnectionPool, table: LiteralString, semaphore: threading.Semaphore) -> str:
    connection = None
    cursor = None

    try:
        with semaphore:
            if not table.isidentifier():
                raise ValueError(f"Invalid table name: '{table}'")

            connection = pool.get_connection()
            cursor = connection.cursor()

            cursor.execute(f"SHOW CREATE TABLE `{table}`")
            result = cursor.fetchone()[1]

    except mariadb.Error:
        raise

    finally:
        if cursor: cursor.close()
        if connection: connection.close()

    return result

def create_table(pool: mariadb.ConnectionPool, table: LiteralString, create_table_str: str, semaphore: threading.Semaphore) -> None:
    connection = None
    cursor = None

    try:
        with semaphore:
            if not table.isidentifier():
                raise ValueError(f"Invalid table name: '{table}'")

            connection = pool.get_connection()
            cursor = connection.cursor()

            cursor.execute(f"DROP TABLE IF EXISTS `{table}`")
            cursor.execute(create_table_str)

    except mariadb.Error:
        raise

    finally:
        if cursor: cursor.close()
        if connection: connection.close()

def get_tables(pool: mariadb.ConnectionPool, semaphore: threading.Semaphore) -> List[LiteralString]:
    result = []
    cursor = None
    connection = None

    try:
        with semaphore:
            connection = pool.get_connection()
            cursor = connection.cursor()
            cursor.execute("SHOW TABLES")

            for table in cursor:
                result.append(table[0])

    except mariadb.Error:
        raise

    finally:
        if cursor: cursor.close()
        if connection: connection.close()

    return result

def get_columns(pool: mariadb.ConnectionPool, table: LiteralString, semaphore: threading.Semaphore) -> List[LiteralString]:
    result = []
    cursor = None
    connection = None

    try:
        with semaphore:
            if not table.isidentifier():
                raise ValueError(f"Invalid table name: '{table}'")

            connection = pool.get_connection()
            cursor = connection.cursor()

            cursor.execute(f"SHOW COLUMNS FROM `{table}`")

            for table in cursor:
                result.append(table[0])

    except mariadb.Error:
        raise

    finally:
        if cursor: cursor.close()
        if connection: connection.close()

    return result

def select_data(pool: mariadb.ConnectionPool, table: LiteralString, semaphore: threading.Semaphore) -> List[Tuple]:
    results = []
    cursor = None
    connection = None

    try:
        with semaphore:
            if not table.isidentifier():
                raise ValueError(f"Invalid table name: '{table}'")

            connection = pool.get_connection()
            cursor = connection.cursor()

            query = f"SELECT * FROM `{table}`"
            cursor.execute(query)

            results = cursor.fetchall()
    except mariadb.Error:
        raise

    finally:
        if cursor: cursor.close()
        if connection: connection.close()

    return results

def insert_data(pool: mariadb.ConnectionPool, table: LiteralString, data: List[Tuple], semaphore: threading.Semaphore) -> None:
    connection = None
    cursor = None

    try:
        with semaphore:
            if not table.isidentifier():
                raise ValueError(f"Invalid table name: '{table}'")

            connection = pool.get_connection()
            cursor = connection.cursor()

            cursor.execute(f"SHOW COLUMNS FROM `{table}`")
            column_length = len(cursor.fetchall())

            column_length = len(get_columns(pool, table, semaphore))
            if column_length > 1:
                query = f"INSERT INTO `{table}` VALUES " + '(' + ('?,' * (column_length - 1)) + '?)'
            else:
                query = f"INSERT INTO `{table}` VALUES (?)"

            cursor.executemany(query, data)
            connection.commit()
    except mariadb.Error:
        raise
    finally:
        if connection: connection.close()
        if cursor: cursor.close()


def processing_database_copy(
    source_pool: mariadb.ConnectionPool,
    destination_pool: mariadb.ConnectionPool,
    table: LiteralString,
    source_semaphore: threading.Semaphore,
    destination_semaphore: threading.Semaphore
):
    try:
        with thread_limit_semaphore:  # Enforce global thread limit
            create_table(destination_pool, table, show_create(source_pool, table, source_semaphore), destination_semaphore)
            data = select_data(source_pool, table, source_semaphore)
            insert_data(destination_pool, table, data, destination_semaphore)
            print(f"Finished processing table: {table}")
    except Exception as e:
        print(f"Error processing table {table}: {e}", file=sys.stderr)

def main():
    threads = []

    try:
        tables = get_tables(source_pool, source_semaphore)

        for table in tables:
            thread = threading.Thread(
                target=processing_database_copy,
                args=(source_pool, destination_pool, table, source_semaphore, destination_semaphore)
            )
            threads.append(thread)
            thread.start()

        # Wait for all threads to complete
        for thread in threads:
            thread.join()

        print("All tables processed successfully")
    except Exception as e:
        print(f"Error during database copy: {e}", file=sys.stderr)
        sys.exit(1)
    finally:
        source_pool.close()
        destination_pool.close()

if __name__ == '__main__':
    main()
