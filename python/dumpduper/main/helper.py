#!/usr/bin/env python3
# import mariadb
from datetime import datetime

def get_tables(connection):
    tables = []
    cursor = connection.cursor()
    cursor.execute("SHOW TABLES")

    for table_tuple in cursor.fetchall():
        tables.append(table_tuple[0])

    cursor.close()
    return tables


def convert_tuple(tup):
    tuple_string = "("
    for index, elem in enumerate(tup):
        if elem is None:
            tuple_string += "NULL"
        elif isinstance(elem, int):
            tuple_string += str(elem)
        elif isinstance(elem, str):
            tuple_string += f"'{elem}'"
        elif isinstance(elem, datetime):
            tuple_string += f"'{datetime.strftime(elem, "%Y-%m-%d %H:%M:%S")}'"

        if not index == len(tup) - 1:
            tuple_string += ','

    return tuple_string + ")"
