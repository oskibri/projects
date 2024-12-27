import socket
import threading

def connect_to_server():
    with socket.create_connection(("localhost", 8080)) as client_socket:
        response = client_socket.recv(1024)
        print("Received:", response.decode())

# Create and start multiple threads to simulate concurrent connections
threads = []
for i in range(10):  # Try connecting with 10 clients
    thread = threading.Thread(target=connect_to_server)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()
