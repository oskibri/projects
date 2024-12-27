import threading
import queue
from time import sleep
from collections import deque

threads = []
q = queue.Queue()
s = deque()

def myt(tid):
    q.put(f"snibri: {tid}")
    s.append(f"stackbri: {tid}")

def main():
    for tid in range(1000):
        threads.append(threading.Thread(target=myt, args=(tid,)))

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    while not q.empty():
        print(q.get())

    while s:
        print(s.pop())


if __name__ == "__main__":
    main()
