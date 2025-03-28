import socket
import MyRSA as MyAlg

PLAIN_TEXT = "Sauce ki kamaal"

s = socket.socket()
s.bind(('', 12345))

s.listen(5)

c, addr = s.accept()
print(f"Connected to client with the address: {addr}")

print(f"Message from client: {s.recv(1024).decode()}")

c.send("Hello from server")

msg = c.recv(1024)
if msg.decode() == "REQUEST":
    print("Received connection request from the client")
    private_key, public_key = MyAlg.generate_key()
    print(f"Private key: {private_key}, Public key: {public_key}")
    c.send(f"{" ".join(public_key)}")
    print("Sent the public key to the client")
else:
    print("Error: Expected connection request at this stage")
    exit()

msg = c.recv(1024).decode()
print(f"Encrypted message received: {msg}")
dm = MyAlg.decrypt(msg, key=private_key)
print(f"Decrypted message: {dm}")

print()

c.send("REQUEST")
print("Connection request initiated")
key = map(int, c.recv(1024).decode().split())
print(f"Key received: {key}")

print(f"Message to be sent: {PLAIN_TEXT}")
encrypted = MyAlg.encrypt(PLAIN_TEXT, key=key)
print("Encrypted text:", encrypted)
s.send(encrypted.encode())