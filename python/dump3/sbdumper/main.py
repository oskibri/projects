#!/usr/bin/env python3
from sbdumper.parser import args, RED, RESET
import sys
import mariadb
import threading
import time


class dumper:
    def __init__(self, db, host, user, passwd, port, threads, verbose=False):
        self.database = db
        self.hostname = host
        self.username = user
        self.password = passwd
        self.port = port

        self.__lock = threading.Lock()

        self.__threads = threads
        self.__verbose = verbose

        self.__cursors = []
        self.__thread_arr = []

        try:
            self.__connection = mariadb.connect(db=db, host=host, user=user, passwd=passwd, port=port)
        except mariadb.Error as e:
            print(f"Failed to create connection: {e}", file=sys.stderr)
            if self.__verbose: 
                [print(f"{RED}Missing value for: {k}{RESET}", file=sys.stderr) for k,v in self.__dict__.items() if v is None]
            sys.exit(1)

        try:
            self.__master_cur = self.__connection.cursor()
        except mariadb.Error as e:
            print(f"Failed to create master cursor: {e}", file=sys.stderr)
            sys.exit(1)


    # Private functions
    def __close_connection(self):
        try:
            self.__connection.close()
        except mariadb.Error as e:
            print(f"Failed to close connection: {e}", file=sys.stderr)
            sys.exit(1)

    def __close_cursors(self):
        # Close child cursors
        for i,curid in enumerate(self.__cursors):
            if self.__verbose: 
                print(f"Closing curid {i}: {curid}")
            try:
                curid.close()
            except mariadb.Error as e:
                print(f"Failed to close cursor, curid {i}: {e}", file=sys.stderr)
                sys.exit(1)
        # Close master cursor
        self.__master_cur.close()

    def __thread(self, function, *args):
        try:
            self.__thread_arr.extend(threading.Thread(target=function, args=(*args, tid)) for tid in range(self.__threads))
            [thread.start() for thread in self.__thread_arr]
            [thread.join() for thread in self.__thread_arr]
        except Exception as e:
            print(f"Threading failed: {e}", file=sys.stderr)
            sys.exit(1)
        self.__thread_arr = []

    def __get_tables(self):
        try:
            self.__master_cur.execute("SHOW TABLES")
        except mariadb.Error as e:
            print(f"Failed to SHOW TABLES: {e}", file=sys.stderr)
            sys.exit(1)
        return [table[0] for table in self.__master_cur.fetchall()]


    # Public functions
    def iniate(self):
        for i in range(self.__threads):
            try:
                curid = self.__connection.cursor()
                if self.__verbose: 
                    print(f"Creating curid {i}: {curid}")
                self.__cursors.append(curid)
            except mariadb.Error as e:
                print(f"Failed to create cursor, curid {i}: {e}", file=sys.stderr)
                sys.exit(1)

    def close(self):
        self.__close_cursors()
        self.__close_connection()

    def print_curids(self):
        for i,curid in enumerate(self.__cursors):
            print(f"Printing curid {i}: {curid}")

    def print_tables(self):
        table_index = 0

        def t_print_tables(tables, tid):
            nonlocal table_index
            while True:
                self.__lock.acquire()

                if table_index >= len(tables):
                    self.__lock.release()
                    return 

                print(tid, tables[table_index])
                table_index += 1

                self.__lock.release()
                #time.sleep(1)

        self.__thread(t_print_tables, self.__get_tables())

    def print_data(self):
        table_index = 0

        def t_print_data(tables, tid):
            nonlocal table_index
            while True:
                self.__lock.acquire()

                if table_index >= len(tables):
                    self.__lock.release()
                    return

                current_index = table_index
                table_index += 1

                self.__cursors[0].execute(f"SELECT * FROM `{tables[current_index]}`")
                self.__lock.release()

                [print(tid, tables[current_index], output) for output in self.__cursors[0].fetchall()]
                #time.sleep(.5)


        self.__thread(t_print_data, self.__get_tables())

def main():
    dbimport = dumper(
        args.database_import, 
        args.hostname_import, 
        args.username_import, 
        args.password_import, 
        args.portnumber_import,
        args.threads,
        args.verbose)

    dbimport.iniate()
    #dbimport.print_curids()
    #dbimport.print_tables()
    dbimport.print_data()
    dbimport.close()

if __name__ == "__main__":
    main()
