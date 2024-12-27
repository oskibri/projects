import mariadb

connection = mariadb.connect(
        host="localhost",
        user="oskar",
        password="snibri",
        database="test"
)

client_version = mariadb.__version__
print(f"MairaDB Client Version: {client_version}")

server_version = connection.get_server_version()
print(f"MariaDB Server Version: {server_version}")

server_version_str = connection.server_version
print(f"MariaDB Server Version String: {server_version_str}")

connection.close()
