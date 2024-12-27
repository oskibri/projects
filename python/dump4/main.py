import mariadb
import concurrent.futures
import logging
import argparse
import os
import sys

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(message)s', datefmt='%Y-%m-%d %H:%M:%S')

# Parse user arguments
parser = argparse.ArgumentParser()
parser.add_argument('-mt', '--max_threads', default=5, type=int)
parser.add_argument('-sh', '--source_host', default='localhost')
parser.add_argument('-su', '--source_user', default=os.getlogin())
parser.add_argument('-sp', '--source_pass')
parser.add_argument('-sd', '--source_db')
parser.add_argument('-sP', '--source_port', default=3306, type=int)
parser.add_argument('-dh', '--dest_host', default='localhost')
parser.add_argument('-du', '--dest_user', default=os.getlogin())
parser.add_argument('-dp', '--dest_pass')
parser.add_argument('-dd', '--dest_db')
parser.add_argument('-dP', '--dest_port', default=3306, type=int)
args = parser.parse_args()

MAX_THREADS = args.max_threads

# Database connection parameters
SOURCE_DB_CONFIG = {
    "pool_name": "source_pool",
    "pool_size": MAX_THREADS,
    "host": args.source_host,
    "user": args.source_user,
    "password": args.source_pass,
    "database": args.source_db,
    "port": args.source_port
}

DEST_DB_CONFIG = {
    "pool_name": "dest_pool",
    "pool_size": MAX_THREADS,
    "host": args.dest_host,
    "user": args.dest_user,
    "password": args.dest_pass,
    "database": args.dest_db,
    "port": args.dest_port
}

def copy_table(table_name: str, source_pool: mariadb.ConnectionPool, dest_pool: mariadb.ConnectionPool):
    """Worker function to copy a single table."""
    source_conn = None
    dest_conn = None
    source_cursor = None
    dest_cursor = None
    try:
        # Establish source and destination connections
        source_conn = source_pool.get_connection()
        dest_conn = dest_pool.get_connection()
        source_cursor = source_conn.cursor()
        dest_cursor = dest_conn.cursor()

        logging.info(f"Copying table: {table_name}")

        # Fetch column names and types
        source_cursor.execute(f"DESCRIBE {table_name}")
        columns = source_cursor.fetchall()
        column_names = [col[0] for col in columns]

        # Create table in the destination database
        create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} ("
        create_table_query += ", ".join([f"{col[0]} {col[1]}" for col in columns])
        create_table_query += ")"
        dest_cursor.execute(create_table_query)

        # Insert rows into the destination table
        fetch_size = 1000
        source_cursor.execute(f"SELECT * FROM {table_name}")
        while True:
            rows = source_cursor.fetchmany(fetch_size)
            if not rows:
                break
            insert_query = f"INSERT INTO {table_name} ({', '.join(column_names)}) VALUES ({', '.join(['%s'] * len(column_names))})"
            dest_cursor.executemany(insert_query, rows)
            dest_conn.commit()

        logging.info(f"Finished copying table: {table_name}")
    except Exception as e:
        logging.error(f"Error copying table {table_name}: {e}")
    finally:
        if isinstance(source_conn, mariadb.Connection): source_conn.close()
        if isinstance(source_cursor, mariadb.Cursor): source_cursor.close()
        if isinstance(dest_conn, mariadb.Connection): dest_conn.close()
        if isinstance(dest_cursor, mariadb.Cursor): dest_cursor.close()

def main():
    try:
        source_pool = mariadb.ConnectionPool(**SOURCE_DB_CONFIG)
    except Exception as e:
        logging.error(f"Error trying to connect to source database: {e}")
        return

    try:
        dest_pool = mariadb.ConnectionPool(**DEST_DB_CONFIG)
    except Exception as e:
        source_pool.close()
        logging.error(f"Error trying to connect to destination database: {e}")
        return

    # Fetch list of tables from the source database
    try:
        conn = source_pool.get_connection()
        cursor = conn.cursor()
        cursor.execute("SHOW TABLES")
        tables = [row[0] for row in cursor.fetchall()]
        cursor.close()
        conn.close()
    except Exception as e:
        logging.error(f"Error fetching tables: {e}")
        return

    # Use a thread pool to copy tables
    with concurrent.futures.ThreadPoolExecutor(max_workers=MAX_THREADS) as executor:
        futures = {executor.submit(copy_table, table, source_pool, dest_pool): table for table in tables}
        for future in concurrent.futures.as_completed(futures):
            table = futures[future]
            try:
                future.result()
            except Exception as exc:
                logging.error(f"Table {table} generated an exception: {exc}")

    source_pool.close()
    dest_pool.close()

if __name__ == "__main__":
    main()
