#!/usr/bin/env python3
import mariadb, sys, io, os, argparse, threading
from datetime import datetime

lock = threading.Lock()

def parse_args():
    parser = argparse.ArgumentParser(description="A MySQL/MariaDB SQL dumper")
    parser.add_argument("-d", "--database", type=str, help="The database to dump")
    parser.add_argument("-H", "--hostname", default="localhost", type=str, help="The hostname that the database lives on")
    parser.add_argument("-u", "--username", default=os.getlogin(), type=str, help="The database user to connect to. Takes your shell username if not explicitly set")
    parser.add_argument("-p", "--password", type=str, help="The database user's password")
    parser.add_argument("-t", "--threads", default=1, type=int, help="Number of threads to use. Default is 1024")
    parser.add_argument('full', nargs='?')
    return parser.parse_args()

def parse_pos_args(argstr, args):
    if '@' not in argstr:
        args.database = argstr
    else:
        userpass, dbhost = argstr.split('@', 1)
        if ':' in userpass:
            args.username, args.password = userpass.split(':', 1)
        else:
            args.username = userpass

        if ':' in dbhost:
            args.database, args.hostname = dbhost.split(':', 1)
        else:
            args.database = dbhost

def run(cursor, file):
    lock.acquire()
    with cursor as cur:
        cur.execute("SHOW TABLES")
        tables = cur.fetchall()
        for table, in tables:
            file.write(f"-- Table structure: `{table}`\n\n")
            file.write(f"DROP TABLE IF EXISTS `{table}`;\n")
            query = f"SHOW CREATE TABLE `{table}`"
            cur.execute(query)
            file.write(cur.fetchone()[1] + ";\n\n")
    
            file.write(f"-- Table dump: `{table}`\n\n")
            file.write(f"LOCK TABLES `{table}` WRITE;\n")
            file.write(f"ALTER TABLE `{table}` DISABLE KEYS;\n")
            query = f"SELECT * FROM `{table}`"
    
            cur.execute(query)
            datas = cur.fetchall()
            if datas:
                file.write(f"INSERT INTO `{table}` VALUES\n")
    
                for i, data in enumerate(datas):
    
                    formattet = []
                    for field in data:
                        if field is None:
                            formattet.append("NULL")
                        elif isinstance(field, datetime):
                            formattet.append(f"'{field.strftime('%Y-%m-%d %H:%M:%S')}'")
                        else:
                            formattet.append(f"'{field}'" if isinstance(field, str) else str(field))
    
                    row = "(" + ",".join(formattet) + ")"
                    if i == len(datas) - 1:
                        file.write(row + ";\n")
                        break
                    file.write(row + ",\n")
    
            file.write(f"ALTER TABLE `{table}` ENABLE KEYS;\n")
            file.write(f"UNLOCK TABLES;\n\n")
    lock.release()

def main():
    args = parse_args()
    if args.full: parse_pos_args(args.full, args)

    try:
        conn = mariadb.connect(db=args.database, passwd=args.password, user=args.username)
    except mariadb.Error as e:
        print(e, file=sys.stderr)
        exit(1)
    
    if conn.server_version <= 40103:
        print(f"MySQL server version ({conn.server_info}) is lower than recommended version 4.1.3 (released April 2004)\nUse mysqldump/mariadb-dump client instead", file=sys.stderr)
        sys.exit(2)
    
    file = io.open("./output.txt", "w")
    file.write("-- Server version:\t" + conn.server_info + "\n\n")
    
    threads = [threading.Thread(target=run, args=(conn.cursor(), file)) for _ in range(args.threads)]
    [thread.start() for thread in threads]
    [thread.join() for thread in threads]
    #run(conn.cursor(), file) 
    
    file.close()
    conn.close()

if __name__ == "__main__":
    main()
