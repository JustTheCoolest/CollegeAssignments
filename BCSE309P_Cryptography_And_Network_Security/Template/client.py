import socket

s = socket.socket()
s.connect(('localhost', 12345))

s.send("Hello from client".encode())

msg = s.recv(1024)
print("Server's message:", msg.decode())