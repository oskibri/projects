import mariadb, threading, time

conn = mariadb.connect(db='test', passwd='snibri')
cur1 = conn.cursor()
cur2 = conn.cursor()

lock = threading.Lock()

def run(cursor):
    lock.acquire()
    cursor.execute("SELECT * FROM simple")
    print(cursor.fetchone())
    lock.release()
    time.sleep(.1)

thread1 = threading.Thread(target=run, args=(cur1,))
thread2 = threading.Thread(target=run, args=(cur1,))
thread1.start()
thread2.start()
thread1.join()
thread2.join()

#run(cur1)
#run(cur2)

cur1.close()
cur2.close()
conn.close()
