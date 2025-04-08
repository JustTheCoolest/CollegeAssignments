import socket
from MySHA import sha256

s = socket.socket()
s.bind(('', 12345))
s.listen(5)

print("Server is listening for connections...")
c, addr = s.accept()
print(f"Connected to client with the address: {addr}")

# Receive the message from the client
message = c.recv(1024).decode()
print(f"Message received from client: {message}")

# Compute the hash of the received message
received_hash = c.recv(1024).decode()
print(f"Hash received from client: {received_hash}")

computed_hash = sha256(message)
print(f"Hash computed on server: {computed_hash}")

# Verify the hash
if received_hash == computed_hash:
    print("Hash verification successful! The message integrity is intact.")
    c.send("Hash verified successfully!".encode())
else:
    print("Hash verification failed! The message integrity is compromised.")
    c.send("Hash verification failed!".encode())

c.close()