#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <pthread.h>

// Configuration structure
typedef struct {
    char *host;
    char *user;
    char *password;
    char *database;
    int port;
} DBConfig;

// Thread arguments
typedef struct {
    char *table_name;
    DBConfig *source_config;
    DBConfig *dest_config;
} ThreadArgs;

// Function to connect to the database
MYSQL* connect_to_db(DBConfig *config) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, config->host, config->user, config->password, config->database, config->port, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

// Function to copy a table
void* copy_table(void *args) {
    ThreadArgs *thread_args = (ThreadArgs*)args;
    MYSQL *source_conn = connect_to_db(thread_args->source_config);
    MYSQL *dest_conn = connect_to_db(thread_args->dest_config);

    if (!source_conn || !dest_conn) {
        return NULL;
    }

    char query[1024];
    sprintf(query, "DESCRIBE %s", thread_args->table_name);

    if (mysql_query(source_conn, query)) {
        fprintf(stderr, "Error describing table %s: %s\n", thread_args->table_name, mysql_error(source_conn));
        goto cleanup;
    }

    MYSQL_RES *result = mysql_store_result(source_conn);
    if (!result) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(source_conn));
        goto cleanup;
    }

    // Create table in destination
    sprintf(query, "CREATE TABLE IF NOT EXISTS %s (", thread_args->table_name);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        strcat(query, row[0]);
        strcat(query, " ");
        strcat(query, row[1]);
        strcat(query, ", ");
    }
    query[strlen(query) - 2] = ')'; // Replace last comma
    if (mysql_query(dest_conn, query)) {
        fprintf(stderr, "Error creating table %s: %s\n", thread_args->table_name, mysql_error(dest_conn));
        goto cleanup;
    }

    // Copy data
    sprintf(query, "SELECT * FROM %s", thread_args->table_name);
    if (mysql_query(source_conn, query)) {
        fprintf(stderr, "Error fetching data from %s: %s\n", thread_args->table_name, mysql_error(source_conn));
        goto cleanup;
    }

    result = mysql_store_result(source_conn);
    unsigned int num_fields = mysql_num_fields(result);
    MYSQL_BIND bind[num_fields];
    memset(bind, 0, sizeof(bind));

    // Implement row fetching and inserting here...

cleanup:
    if (source_conn) mysql_close(source_conn);
    if (dest_conn) mysql_close(dest_conn);
    free(thread_args);
    return NULL;
}

// Main function
int main(int argc, char **argv) {
    DBConfig source_config = {"localhost", "root", "password", "source_db", 3306};
    DBConfig dest_config = {"localhost", "root", "password", "dest_db", 3306};

    char *tables[] = {"table1", "table2"}; // Example tables
    int table_count = sizeof(tables) / sizeof(tables[0]);

    pthread_t threads[table_count];
    for (int i = 0; i < table_count; i++) {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args->table_name = tables[i];
        args->source_config = &source_config;
        args->dest_config = &dest_config;

        if (pthread_create(&threads[i], NULL, copy_table, args) != 0) {
            fprintf(stderr, "Error creating thread for table %s\n", tables[i]);
        }
    }

    for (int i = 0; i < table_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
