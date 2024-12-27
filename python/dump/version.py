import mariadb

connection = mariadb.connect(
        host="localhost",
        user="oskar",
        password="snibri",
        database="test"
)

cursor = connection.cursor()
cursor.execute("SELECT * FROM users")
sql = "INSERT INTO users2 (id, username, age, email, created) VALUES (%s, %s, %s, %s, %s)"

for row in cursor.fetchall():
    cursor.execute(sql, row)
connection.commit()

cursor.execute("SHOW VARIABLES LIKE '%collat%'")
print(cursor.fetchall())
cursor.close()

client_version = mariadb.__version__
print(f"MairaDB Client Version: {client_version}")

server_version = connection.get_server_version()
print(f"MariaDB Server Version: {server_version}")

server_version_str = connection.server_version
print(f"MariaDB Server Version String: {server_version_str}")

connection.close()
