import socket
import MyDiffieHellman
import MyElgamalDSS as MyDSS

port = 1500

def get_my_addr():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return (ip_address, port)

s = socket.socket()
s.connect(('localhost', port))

print("With plain Diffie-Hellman:")

# Send p and g to Alice
p, g = MyDiffieHellman.get_shared_initial_value()

# Generate Bob's private and public keys
bob_private = MyDiffieHellman.get_private_key(p)
bob_public = MyDiffieHellman.get_public_key(g, bob_private, p)
print(f"My private key (not sent): {bob_private}")
print(f"My public key (sent): {bob_public}")

# Send p, g, and Bob's public key to Alice
s.send(f"{p} {g} {bob_public}".encode())
print(f"Sent p, g, and public key to Alice: p={p}, g={g}, bob_public={bob_public}")

# Receive Alice's public key
msg = s.recv(1024).decode()
alice_public = int(msg)
print(f"Public key received from Alice: {alice_public}")

# Compute shared secret
shared_secret = MyDiffieHellman.get_shared_secret(alice_public, bob_private, p)
print(f"Shared secret: {shared_secret}")

print()

print("Diffie-Hellman with DSS:")

# Send p, g, and Bob's public key to Alice
s.send(f"{p} {g} {bob_public}".encode())
print(f"Sent p, g, and public key to Alice: p={p}, g={g}, bob_public={bob_public}")

# Receive Alice's public key, DSS public key, identifier, and signature
msg = s.recv(1024).decode()
alice_public, alice_dss_public, alice_identifier, alice_signature = msg.split(' ', 3)
alice_public = int(alice_public)
alice_dss_public = int(alice_dss_public)
alice_signature = tuple(map(int, alice_signature.split()))
print(f"Received Alice's public key, DSS public key, identifier, and signature: {alice_public}, {alice_dss_public}, {alice_identifier}, {alice_signature}")

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

# Send Bob's DSS public key, identifier, and signature
bob_identifier = get_my_addr()
bob_signature = MyDSS.get_signature(
    (bob_identifier, bob_public, alice_identifier, alice_public),
    bob_dss_private
)
s.send(f"{bob_dss_public} {bob_identifier} {bob_signature}".encode())
print(f"My DSS public key, identifier, and signature (sent): {bob_dss_public}, {bob_identifier}, {bob_signature}")