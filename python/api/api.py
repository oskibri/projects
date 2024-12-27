import os
import sys
import ssl
import json
from http.server import BaseHTTPRequestHandler, HTTPServer

USER_TOKENS = {
    "ADMIN1234": "admin",
    "HELLO1234": "oskar"
}

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def __create_message(self, message, loglevel=None, response_code=None):

        if loglevel == None: loglevel = "message"
        if response_code == None: response_code = 200

        response = json.dumps({loglevel: message})
        response_bytes = response.encode("utf-8")

        self.send_response(response_code)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(response)))
        self.end_headers()

        return response_bytes

    def do_GET(self):
        auth_header = self.headers.get('Authorization')

        if auth_header and auth_header.startswith("Bearer "):
            token = auth_header.split("Bearer ")[1]

            user = USER_TOKENS.get(token)

            if user:
                if self.path == '/':
                    msg = self.__create_message(f"Welcome to the API, {user}!", "message", 200)
                    self.wfile.write(msg)

                elif self.path.startswith('/hello/'):
                    username = self.path.split("/hello/")[1]
                    username = username.split('/')[0]
                    msg = self.__create_message(f"Hello there {username}", "message", 200)
                    self.wfile.write(msg)

                else:
                    msg = self.__create_message("Unknown path", "error", 404)
                    self.wfile.write(msg)
            else:
                # Token is invalid
                msg = self.__create_message(
                    response_code=401,
                    message="Unauthorized: Token is invalid",
                    loglevel="error"
                )
                self.wfile.write(msg)

        else:
            # User is invalid
            msg = self.__create_message(
                "Unauthorized: User invalid",
                "error",
                401
            )
            self.wfile.write(msg)

def daemonize():
    if os.fork() > 0:
        sys.exit()

    os.setsid()
    if os.fork() > 0:
        sys.exit()

    sys.stdout.flush()
    sys.stderr.flush()

    with open("/dev/null", "w+") as dev_null:
        os.dup2(dev_null.fileno(), sys.stdin.fileno())
        os.dup2(dev_null.fileno(), sys.stdout.fileno())
        os.dup2(dev_null.fileno(), sys.stderr.fileno())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000, daemon=False):
    if daemon:
        daemonize()

    server_address = ('', port)
    httpd = server_class(server_address, handler_class)

    ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ctx.load_cert_chain(certfile="ssl/fullchain.pem", keyfile="ssl/private.key")

    httpd.socket = ctx.wrap_socket(httpd.socket, server_side=True)

    print(f'Starting HTTPS server on port {port}')
    httpd.serve_forever()

if __name__ == "__main__":
    daemon_mode = '--daemon' in sys.argv
    run(daemon=daemon_mode)
