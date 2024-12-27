#!/usr/bin/env python3
from contextlib import contextmanager
import sys
import mariadb
import threading
import configparser
import types

config = configparser.ConfigParser()
config.read('my.cnf')

pool_config = {
    "pool_name": "mypool",
    "pool_size": 5,
    "host": "localhost",
    "port": 3306,
    "user": "oskar",
    "password": "snibri",
    "database": "test"
}

#pool_config = dict(config.items("db"))

try:
    pool = mariadb.ConnectionPool(**pool_config)
    print("Connection pool created successfully")
except mariadb.Error as e:
    print(f"Error creating the connection pool: {e}", file=sys.stderr)
    sys.exit(1)

def execute_query(query, results, tid):
    try:
        conn = pool.get_connection()
        cursor = conn.cursor()
        cursor.execute(query)
        results[tid] = cursor.fetchall()

        cursor.close()
        conn.close()
    except mariadb.Error as e:
        print(f"Error execting query: {e}", file=sys.stderr)
        sys.exit(1)

query = "SELECT * FROM users"

num_threads = 99
results = [[None] for _ in range(num_threads)]
print(results)
threads = [threading.Thread(target=execute_query, args=(query, results, tid)) for tid in range(num_threads)]
[thread.start() for thread in threads]
[thread.join() for thread in threads]

for i,result in enumerate(results):
    for row in result:
        if row is None:
            print(f"Something went wrong with row {i}, result: {row}")
            continue
        #print(row)

