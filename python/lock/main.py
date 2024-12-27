import threading
from time import sleep

counter = 0
lock = threading.Lock()
sema = threading.Semaphore(5)

def increment(thread_id):
    global counter
    print(f"\x1b[31;1mThread {thread_id} attempting to acquire lock...\x1b[0m")
    # with lock:
    with sema:
        print(f"Thread {thread_id} acquired lock")
        sleep(1)
        local_copy = counter
        local_copy += 1
        counter = local_copy
        print(f"Thread {thread_id} increment counter to {counter}")
    print(f"Thread {thread_id} released lock\n\n")

try:
    threads = [threading.Thread(target=increment, args=(i,)) for i in range(20)]
    [thread.start() for thread in threads]
    [thread.join() for thread in threads]
except Exception as e:
    print(e)

# sleep(1)

print(f"Final counter value: {counter}")
