import mariadb


try:
    conn = mariadb.connect(db="test", passwd="snibri")
except mariadb.Error as e:
    print(e)
    exit(1)

with conn.cursor() as cur:
    try:
        cur.execute("CREATE TABLE IF NOT EXISTS oskar (name varchar(100), age int)")
        print(conn.show_warnings())
        conn.commit()

        print(conn.client_capabilities)
        print(conn.server_capabilities)
        print(conn.extended_server_capabilities)

        cur.execute("SHOW CREATE TABLE simple")
        output = cur.fetchone()[1]
        if "ENGINE=InnoDB" in output:
            try:
                output = output.replace("ENGINE=InnoDB", "ENGINE=MyISAM")
            except Exception as e:
                print(e)
        print(output)


        cur.execute("SHOW TABLES")
        output = cur.fetchall()
        for table, in output:
            print(table)
    except mariadb.Warning as w:
        conn.show_warnings()
        print(w)

conn.close()
