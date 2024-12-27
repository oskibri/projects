import threading
import time
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-t', "--threads", default=1, help="Number of threads to use. Default is 1")
args = parser.parse_args()
args.threads = int(args.threads)

index = 0
alph = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

lock = threading.Lock()

def print_letters(tid):
    global index
    while True:
        lock.acquire()
        if index >= len(alph):
            lock.release()
            break  # Exit the loop if index is out of bounds
        print(f"Tid: {tid}", alph[index])
        index += 1
        lock.release()
        time.sleep(.1)

def main():
    threads = [threading.Thread(target=print_letters, args=(i,)) for i in range(args.threads)]
    [thread.start() for thread in threads]
    [thread.join() for thread in threads]

if __name__ == "__main__":
    main()

