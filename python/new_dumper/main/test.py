#!/usr/bin/env python3
import mariadb
import os
from datetime import datetime

pool_config = {
    "pool_name": "test",
    "pool_size": 5,
    "db": "test",
    "host": "localhost",
    "user": os.getlogin(),
    "passwd": "snibri"
}

def to_raw(result):
    #fields = (field for row in result for field in row)
    for j,row in enumerate(result):
        new_row = list(row)
        for i,field in enumerate(new_row):
            if field is None:
                new_row[i] = "NULL"
            elif isinstance(field, datetime):
                new_row[i] = field.strftime("%Y-%m-%d %H:%M:%S")
        result[j] = new_row
    return result


pool = mariadb.ConnectionPool(**pool_config)

conn = pool.get_connection()
cur = conn.cursor()
cur.execute("SELECT * FROM simple")
res = cur.fetchall()

res = to_raw(res)
print(res)

cur.close()
conn.close()
pool.close()
