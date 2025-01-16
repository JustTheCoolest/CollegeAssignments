PLAINTEXT = "VIT is a great university"

import socket
import MyDES

s = socket.socket()
s.connect(('localhost', 12345))

s.send("Hello from client".encode())

msg = s.recv(1024)
print("Server's message:", msg.decode())

print("Message to send to server: ", PLAINTEXT)

encrypted = MyDES.encrypt(PLAINTEXT, seed=101)
print("Encrypted text:", encrypted)
s.send(encrypted.encode())

msg = s.recv(1024)
print("Encrypted text received:", msg.decode())
print("Decrypted text:", MyDES.decrypt(msg.decode(), seed=101))
