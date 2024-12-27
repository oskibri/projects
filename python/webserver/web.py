import socket, time

def run(host='0.0.0.0', port=8080):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ssocket:
        ssocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        ssocket.bind((host, port))
        ssocket.listen(5)
        print(f'Server running on http://{host}:{port}')

        while True:
            csocket, caddr = ssocket.accept()
            print(f'Connection from {caddr}')
            time.sleep(10)

            with csocket:
                #req = csocket.recv(1024).decode('utf-8')
                #print(f'Request:\n{req}')

                res = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, world!\n"
                csocket.sendall(res.encode('utf-8'))

if __name__ == "__main__":
    run()
