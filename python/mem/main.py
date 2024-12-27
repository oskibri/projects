import psutil, sys
from os import getpid

if len(sys.argv) > 2:
    print(sys.stderr, f'Too many arguments passed\nUsage: {sys.argv[0]} <PID>')
    exit(1)

def main():
    pid = int(sys.argv[1]) if len(sys.argv) > 1 else getpid()

    try:
        proc = psutil.Process(pid)
        rss = proc.memory_info().rss
        rss_mb = rss / (1024 ** 2)
        print(f'RSS memory: {rss_mb:.2f} mb')
    except Exception as e:
        print(e)
        exit(2)

if __name__ == "__main__":
    main()
