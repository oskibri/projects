#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char** argv) {
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int num_fields;
	MYSQL_FIELD *fields;

	printf("%u\n", mysql_thread_safe());
	exit(1);

	if (!(conn = mysql_init(0)))
	{
		fprintf(stderr, "unable to initialize connection struct\n");
		exit(1);
	}

	if (!mysql_real_connect(
		conn,
		"localhost",
		"oskar",
		"snibri",
		"test",
		3306,
		NULL,
		0
	))
	{
		fprintf(stderr, "Error connecting to Server: %s\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	mysql_query(conn, "SELECT * FROM `simple`");
	result = mysql_store_result(conn);
	num_fields = mysql_num_fields(result);
	fields = mysql_fetch_fields(result);

	for (int i = 0; i < num_fields; i++) {
		printf("%s\t", fields[i].name);
	}
	printf("\n");

	printf("%s\t", mysql_fetch_row(result)[0]);
	printf("%s\n", mysql_fetch_row(result)[1]);
	printf("%s\t", mysql_fetch_row(result)[0]);
	printf("%s\n", mysql_fetch_row(result)[1]);
	printf("%s\t", *mysql_fetch_row(result));
	printf("%s\t", *mysql_fetch_row(result));
	printf("%s\t\n", *mysql_fetch_row(result));

	// while ((row = mysql_fetch_row(result))) {
	// 	for (int i = 0; i < num_fields; i++) {
	// 		printf("%s\t", row[i] ? row[i] : "NULL");
	// 	}
	// 	printf("\n");
	// }

	mysql_free_result(result);
	mysql_close(conn);

	return 0;
}
