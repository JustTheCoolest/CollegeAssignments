import socket

s = socket.socket()
s.bind(('', 12345))
s.listen(5)

c, addr = s.accept()
print("Connection from: ", addr)

msg = c.recv(1024)
print("Message: ", msg.decode())

c.send("Hello from server".encode())