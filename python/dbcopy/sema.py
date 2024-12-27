import threading

# Semaphore with 2 permits
semaphore = threading.Semaphore(2)

def task(thread_id):
    print(f"Thread {thread_id} waiting to acquire semaphore...")
    semaphore.acquire()
    print(f"Thread {thread_id} acquired semaphore.")
    # Simulate work
    import time; time.sleep(2)
    semaphore.release()
    print(f"Thread {thread_id} released semaphore.")

threads = [threading.Thread(target=task, args=(i,)) for i in range(5)]

for t in threads:
    t.start()

for t in threads:
    t.join()
