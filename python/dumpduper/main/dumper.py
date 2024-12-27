#!/usr/bin/env python3
from datetime import datetime
import mariadb
import comment_code
import threading
from queue import Queue

class dumper:
    def __init__(self, **pool):
        self.__pool: mariadb.ConnectionPool = mariadb.ConnectionPool(**pool)
        connection = self.__pool.get_connection()
        cursor = connection.cursor()

        self.__result_queue = Queue()

        self.__thread_limit = self.__pool.pool_size
        self.__semaphore = threading.Semaphore(self.__thread_limit)
        self.lock = threading.Lock()

        self.client_version = mariadb.__version__

        cursor.execute("SELECT VERSION()")
        self.server_version = cursor.fetchone()[0]

        self.host = connection.server_name
        self.port = connection.server_port
        self.database = connection.database

        self.comment_code_start = comment_code.comment_code_start(self.client_version, self.host, self.database, self.server_version)
        self.comment_code_end = comment_code.comment_code_end

        cursor.close()
        connection.close()

    def get_conn(self):
        return self.__pool.get_connection()

    def simple_query(self, query: str):
        conn = self.get_conn()
        cur = conn.cursor()
        cur.execute(query)
        result = cur.fetchall()
        cur.close()
        conn.close()
        return result

    def get_tables(self):
        tables = []
        tables_tuparr = self.simple_query("SHOW TABLES")
        [tables.append(data[0]) for data in tables_tuparr]
        return tables

    def get_table_data(self, table: str, _use_threads: bool = False) -> list[tuple[str | int | None | datetime]] | None:
        """
        Retrieves data for the specified table.

        Args:
            table (str): The name of the table.
            use_threads (bool, optional): Used internally for threading.
        """
        def get_data(): 
            return self.simple_query(f"SELECT * FROM `{table}`")

        if not _use_threads:
            return get_data()

        with self.__semaphore:
            self.__result_queue.put((table, get_data()))

    def __store_table_data(self):
        threads = []
        using_threads = True

        for table in self.get_tables():
            thread = threading.Thread(target=self.get_table_data, args=(table, using_threads))
            threads.append(thread)
            thread.start()
        [thread.join() for thread in threads]

    def get_database_data(self) -> dict[str, list[tuple[str | int | datetime | None]]]:
        self.__store_table_data()

        all_tables_data = {}
        while not self.__result_queue.empty():
            table, data = self.__result_queue.get()
            all_tables_data[table] = data

        return all_tables_data

    def get_table_creation(self):
        def store_table_creation(table):
            result = self.simple_query(f"SHOW CREATE TABLE `{table}`")
            result = result[0][1]
            with self.__semaphore:
                self.__result_queue.put((table, result))
            
        threads = []
        for table in self.get_tables():
            thread = threading.Thread(target=store_table_creation, args=(table,))
            threads.append(thread)
            thread.start()
        [thread.join() for thread in threads]

        table_creation_array = {}
        while not self.__result_queue.empty():
            table, data = self.__result_queue.get()
            table_creation_array[table] = data

        return table_creation_array

    def close(self):
        self.__pool.close()

