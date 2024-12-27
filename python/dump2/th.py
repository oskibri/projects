import threading
#from datetime import datetime
import time

def print_numbers():
    for i in range(5):
        print(f"Number: {i}")
        time.sleep(.1)

def print_letters():
    for letter in ['A', 'B', 'C', 'D', 'E', 'F']:
        print(f"Letter: {letter}")
        time.sleep(.1)

thread1 = threading.Thread(target=print_numbers)
thread2 = threading.Thread(target=print_letters)

thread1.start()
thread2.start()

thread1.join()
thread2.join()

print("All threads have finished.")
