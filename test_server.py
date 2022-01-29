import https.server
import ssl
import os

os.system("openssl req -new -x509 -keyout server.pem -out server.pem -days 365 -nodes")

httpd = https.server.HTTPServer(('localhost', 4443), https.server.SimpleHTTPRequestHandler)
httpd.socket = ssl.wrap_socket (httpd.socket, certfile='./server.pem', server_side=True)
print("Hosting on: https://localhost:4443")
httpd.serve_forever()