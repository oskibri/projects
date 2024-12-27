import threading

index = 0
alph = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

lock = threading.Lock()

def print_letters(tid):
    global index
    for _ in range(len(alph)):
        lock.acquire()
        if index >= len(alph): break
        print(f"Tid: {tid}", alph[index])
        index += 1
        lock.release()

def main():
    thread1 = threading.Thread(target=print_letters, args=(1,))
    thread2 = threading.Thread(target=print_letters, args=(2,))
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()

if __name__ == "__main__":
    main()
