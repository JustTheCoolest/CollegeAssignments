PLAINTEXT = "Wakanda Forever"

import socket
import MyDES

s = socket.socket()
s.bind(('', 12345))
s.listen(5)

c, addr = s.accept()
print("Connection from: ", addr)

msg = c.recv(1024)
print("Message: ", msg.decode())

c.send("Hello from server".encode())

msg = c.recv(1024)
print("Encrypted text received:", msg.decode())

print("Decrypted text:", MyDES.decrypt(msg.decode(), seed=101))

print("\nMessage to send to client: ", PLAINTEXT)

encrypted = MyDES.encrypt(PLAINTEXT, seed=101)
print("Encrypted text:", encrypted)

c.send(encrypted.encode())
