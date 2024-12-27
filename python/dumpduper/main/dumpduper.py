#!/usr/bin/env python3
from time import sleep
import mariadb
import helper
from dumper import dumper
import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-u', '--user')
parser.add_argument('-p', '--passwd')
parser.add_argument('-d', '--db')
parser.add_argument('-P', '--poolsize')
args = parser.parse_args()

conn_params = {
    "pool_name": "mypool",
    "pool_size": args.poolsize,
    "user": args.user,
    "passwd": args.passwd,
    "database": args.db
}

myd = dumper(**conn_params)

datadata = myd.get_database_data()
creationdata = myd.get_table_creation()

print(myd.comment_code_start)

for table,data in datadata.items():
    print(f"""
--
-- Showing creation of {table}
--
    """)
    print(creationdata[table])

    if data == None:
        print("No data")
    elif data != []:
        print(f"\n--\n-- Showing data from {table}\n--\n\nINSERT INTO `{table}` VALUES", end='')
        for index, row in enumerate(data):
            if index == len(data) - 1:
                print(helper.convert_tuple(row) + ";", end='\n')
            else: 
                print(helper.convert_tuple(row) + ",", end='')
myd.close()

print(myd.comment_code_end)

# pool = mariadb.ConnectionPool(reconnect=True, **conn_params)
#
# conn = pool.get_connection()
# print("Current database: %s" % conn.database)
# cur = conn.cursor()
#
# tables = helper.get_tables(conn)
#
# for table in tables:
#     cur.execute(f"SHOW CREATE TABLE `{table}`")
#     table_creation = cur.fetchone()[1]
#     print(table_creation + "\n")
#
# sys.exit()
#
#
# cur.execute(f"SELECT * FROM `{table}`")
# table_data = cur.fetchall()
# cur.close()
#
# print(table_creation + "\n")
#
# for index, row in enumerate(table_data):
#     row = helper.convert_tuple(row)
#
#     if index == 0:
#         print(f"INSERT INTO `{table}` VALUES", end='')
#     elif index == len(table_data)-1:
#         print(row + ';')
#         break
#
#     print(f"{row},", end='')
#
# conn.close()
# pool.close()
