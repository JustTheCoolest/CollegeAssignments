PLAINTEXT = "Wakanda Forever"

import socket
import MyAES

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

print("Decrypted text:", MyAES.decrypt(msg.decode(), key=MyAES.KEY))

print("\nMessage to send to client: ", PLAINTEXT)

encrypted = MyAES.encrypt(PLAINTEXT, key=MyAES.KEY)
print("Encrypted text:", encrypted)

c.send(encrypted.encode())
