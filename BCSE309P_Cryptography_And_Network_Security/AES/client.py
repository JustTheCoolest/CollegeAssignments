PLAINTEXT = "VIT is a great"

import socket
import MyAES as MyAlg

s = socket.socket()
s.connect(('localhost', 12345))

s.send("Hello from client".encode())

msg = s.recv(1024)
print("Server's message:", msg.decode())

print("Message to send to server: ", PLAINTEXT)

encrypted = MyAlg.encrypt(PLAINTEXT, key=MyAlg.KEY)
print("Encrypted text:", encrypted)
s.send(encrypted.encode())

msg = s.recv(1024)
print("Encrypted text received:", msg.decode())
print("Decrypted text:", MyAlg.decrypt(msg.decode(), key=MyAlg.KEY))
