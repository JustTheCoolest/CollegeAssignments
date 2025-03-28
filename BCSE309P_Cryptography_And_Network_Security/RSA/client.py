PLAINTEXT = "VIT is a great"

import socket
import MyRSA as MyAlg

s = socket.socket()
s.connect(('localhost', 12345))

s.send("Hello from client".encode())

msg = s.recv(1024)
print("Server's message:", msg.decode())

s.send("REQUEST")
print("Sent connection request to server.")

msg = s.recv(1024)
n, e = [int(val) for val in msg.decode().split()]
key = (n, e)
print(f"Key received from server: n={n}, e={e}")

print("Message to send to server: ", PLAINTEXT)

encrypted = MyAlg.encrypt(PLAINTEXT, key=key)
print("Encrypted text:", encrypted)
s.send(encrypted.encode())

msg = s.recv(1024)
if msg.decode() == "REQUEST":
    print("Received connection request from server.")
    private_key, public_key = MyAlg.generate_key()
    print(f"Private key: {private_key}, Public key: {public_key}")
    s.send(f"{public_key[0]} {public_key[1]}".encode())
    print("Sent public key to server.")

msg = s.recv(1024)
print("Encrypted text received:", msg.decode())
print("Decrypted text:", MyAlg.decrypt(msg.decode(), key=private_key))
