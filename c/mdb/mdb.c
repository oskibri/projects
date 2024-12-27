#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "oskar", "", "oskar", 0, NULL, 0);
	mysql_query(conn, "insert into test (name, age) values ('snibri', 99)");
	res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL) {
		printf("ID %s, Name: %s, Age: %s\n", row[0], row[1], row[2]);
	}

	return EXIT_SUCCESS;
}
