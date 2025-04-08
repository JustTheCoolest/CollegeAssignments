import socket
from MySHA import sha256

s = socket.socket()
s.connect(('localhost', 12345))

# Message to send
message = "Hello, this is a secure message."
print(f"Message to send: {message}")

# Compute the hash of the message
message_hash = sha256(message)
print(f"Computed hash: {message_hash}")

# Send the message to the server
s.send(message.encode())
print("Message sent to server.")

# Send the hash to the server
s.send(message_hash.encode())
print("Hash sent to server.")

# Receive verification result from the server
verification_result = s.recv(1024).decode()
print(f"Server's response: {verification_result}")

s.close()