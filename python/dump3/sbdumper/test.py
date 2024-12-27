import threading
import mariadb
import time

# Database connection parameters
DB_CONFIG = {
    "host": "localhost",
    "user": "oskar",
    "passwd": "snibri",
    "port": 3306,
    "db": "test"
}

# Task for Thread 1: Insert rows into a table
def insert_data():
    try:
        # Create a dedicated connection for this thread
        conn = mariadb.connect(**DB_CONFIG)
        cursor = conn.cursor()

        for i in range(5):
            cursor.execute("INSERT INTO table1 (name, age) VALUES (%s, %s)", (f"User{i}", 20 + i))
            conn.commit()
            print(f"Thread 1: Inserted User{i} into table1")
            time.sleep(1)  # Simulate some processing time

    except mariadb.Error as e:
        print(f"Error in Thread 1: {e}")
    finally:
        cursor.close()
        conn.close()

# Task for Thread 2: Fetch rows from a table
def fetch_data():
    try:
        # Create a dedicated connection for this thread
        conn = mariadb.connect(**DB_CONFIG)
        cursor = conn.cursor()

        for _ in range(5):
            cursor.execute("SELECT * FROM table1")
            results = cursor.fetchall()
            print("Thread 2: Fetched rows from table2:")
            for row in results:
                print(row)
            conn.commit()
            time.sleep(1)  # Simulate some processing time

    except mariadb.Error as e:
        print(f"Error in Thread 2: {e}")
    finally:
        cursor.close()
        conn.close()

# Create and start threads
thread1 = threading.Thread(target=insert_data)
thread2 = threading.Thread(target=fetch_data)

thread1.start()
thread2.start()

# Wait for both threads to complete
thread1.join()
thread2.join()

print("Both threads have completed their tasks.")

