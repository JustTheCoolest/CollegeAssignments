import socket
import lab1 as lab

PLAIN_TEXT = "This is the server text"

s = socket.socket()
s.bind(('', 12345))
s.listen(1)

c, addr = s.accept()
print("Connection from: ", addr)

msg = c.recv(1024)

print("Message: ", msg.decode())

c.send("Hello from server".encode())

for cipher in lab.ciphers:
    key = cipher[3]
    msg = c.recv(1024)
    print(f"{cipher[0]} Cipher encrypted text received: ", msg.decode())
    print(f"{cipher[0]} Cipher decrypted text: ", cipher[2](msg.decode(), key))
    print()
    print(f"{cipher[0]} unencrypted text to be sent: ", PLAIN_TEXT)
    encrypted = cipher[1](PLAIN_TEXT, key)
    print(f"{cipher[0]} encrypted text: ", encrypted)
    c.send(encrypted.encode())
    print()

c.close()
s.close()