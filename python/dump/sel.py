import mariadb

connection = mariadb.connect(
        host="localhost",
        user="oskarhesle",
        password="snibri",
        database="oskarhesle"
)

cursor = connection.cursor()

sql = "SELECT * FROM oskarhesle.user"
cursor.execute(sql)
output = cursor.fetchall()

[print(row) for row in output]
cursor.close()

connection.close()
