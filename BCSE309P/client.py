import socket
import lab1 as lab

PLAIN_TEXT = "This is the client text"
PLAIN_TEXT = PLAIN_TEXT.lower().strip()

s = socket.socket()

s.connect(('localhost', 12345))

s.send("Hello from client".encode())

msg = s.recv(1024)
print("Server's message:", msg.decode())

print()

# Handle each cipher
for cipher in lab.ciphers:
    key = cipher[3]
    print(f"\n{cipher[0]} unencrypted text to be sent:", PLAIN_TEXT)
    encrypted = cipher[1](PLAIN_TEXT, key)
    print(f"{cipher[0]} encrypted text:", encrypted)
    s.send(encrypted.encode())
    
    # Receive server's encrypted message
    msg = s.recv(1024)
    print(f"{cipher[0]} Cipher encrypted text received:", msg.decode())
    print(f"{cipher[0]} Cipher decrypted text:", cipher[2](msg.decode(), key))

s.close()