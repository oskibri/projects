#!/usr/bin/env python3
import mariadb, sys

try:
    conn = mariadb.connect(database="test", password="snibri")
    cur = conn.cursor()
except mariadb.Error as e:
    print(e, file=sys.stderr)
    sys.exit(1)

ids = [
    ("gbb", 99, None, "brebbi"),
]
query = "INSERT INTO simple (name, age, email, nickname) VALUES (?, ?, ?, ?) RETURNING id, name, age"

try:
    cur.executemany(query, ids)
    for row in cur:
        print(row)
    conn.commit()
except mariadb.IntegrityError as e:
    print(e, file=sys.stderr)


cur.close()
conn.close()
