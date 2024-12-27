import os
os.environ["MYSQLCLIENT_PURE_PYTHON"] = "1"
import mariadb
from typing import Any, List

def dump_table(dbname: str, tbname: str, tbname_next) -> None:
    try:
        conn = mariadb.connect(
            host="localhost",
            user="oskar",
            password="snibri",
            database=dbname,
            #collation="utf8mb4_unicode_ci",
            #raw=True
        )
        cur = conn.cursor()
    except Exception as e:
        print(e)
        exit(1)

    cur.execute(f"SHOW CREATE TABLE `{tbname}`")
    result1 = cur.fetchone()
    if isinstance(result1, tuple):
        result1 = result1[1]
        if isinstance(result1, bytes):
            result1 = result1.decode('utf-8')
            result1 = result1.replace(tbname, tbname_next)
        else:
            print("error isinstance(result, bytes)")
    else:
        print("error isinstance(result, tuple)")

    if isinstance(result1, str):
        cur.execute(result1)
        conn.commit()
    else:
        print("error isinstance(result, str)")
        

    cur.execute(f"SELECT * FROM {tbname}")
    result: List[Any] = cur.fetchall()
    print(result)
    sql = f"INSERT INTO {tbname_next} (id, username, age, email, created) VALUES (%s, %s, %s, %s, %s)"
    for row in result:
        try:
            cur.execute(sql, row)
            conn.commit()
        except Exception as e:
            print(e)
            exit(1)
    cur.close()
    conn.close()
        
    
dump_table("test", "users", "users5")

