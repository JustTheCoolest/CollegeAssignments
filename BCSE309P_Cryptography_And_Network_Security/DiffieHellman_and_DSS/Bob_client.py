import socket
import MyDiffieHellman
import MyElgmalDSS as MyDSS

port = 12345

def get_my_addr():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return (ip_address, port)

s = socket.socket()
s.connect(('localhost', port))

print("With plain Diffie-Hellman:")

# Send p and g to Alice
p, g = MyDiffieHellman.get_shared_initial_value()
s.send(f"{p} {g}".encode())
print(f"Sent p and g to Alice: p={p}, g={g}")

# Generate Bob's private and public keys
bob_private = MyDiffieHellman.get_private_key(p)
bob_public = MyDiffieHellman.get_public_key(g, bob_private, p)
print(f"My private key (not sent): {bob_private}")
print(f"My public key (sent): {bob_public}")
s.send(str(bob_public).encode())

# Receive Alice's public key
msg = s.recv(1024).decode()
alice_public = int(msg)
print(f"Public key received from Alice: {alice_public}")

# Compute shared secret
shared_secret = MyDiffieHellman.get_shared_secret(alice_public, bob_private, p)
print(f"Shared secret: {shared_secret}")

print()

print("Diffie-Hellman with DSS:")

# Send p and g to Alice
s.send(f"{p} {g}".encode())
print(f"Sent p and g to Alice: p={p}, g={g}")

# Send Bob's public key
s.send(str(bob_public).encode())
print(f"My public key (sent): {bob_public}")

# Receive Alice's DSS public key
msg = s.recv(1024).decode()
alice_dss_public = int(msg)
print(f"DSS public key received from Alice: {alice_dss_public}")

# Receive Alice's public key
msg = s.recv(1024).decode()
alice_public = int(msg)
print(f"Public key received from Alice: {alice_public}")

# Receive Alice's identifier
msg = s.recv(1024).decode()
alice_identifier = msg
print(f"Identifier received from Alice: {alice_identifier}")

# Receive Alice's signature
msg = s.recv(1024).decode()
alice_signature = tuple(map(int, msg.split()))
print(f"Signature received from Alice: {alice_signature}")

# Verify Alice's signature
verification = MyDSS.verify_signature(
    (alice_identifier, alice_public, get_my_addr(), bob_public),
    alice_signature,
    alice_dss_public
)

if not verification:
    print("Signature verification failed. Closing connection.")
    s.close()
else:
    print("Signature verification passed.")

# Generate Bob's DSS keys
bob_dss_private, bob_dss_public = MyDSS.get_keys()
print(f"My DSS private key (not sent): {bob_dss_private}")
print(f"My DSS public key (sent): {bob_dss_public}")
s.send(str(bob_dss_public).encode())

# Send Bob's identifier
bob_identifier = get_my_addr()
print(f"My identifier (sent): {bob_identifier}")
s.send(bob_identifier.encode())

# Sign the message
bob_signature = MyDSS.get_signature(
    (bob_identifier, bob_public, alice_identifier, alice_public),
    bob_dss_private
)
print(f"Signature (sent): {bob_signature}")
s.send(str(bob_signature).encode())