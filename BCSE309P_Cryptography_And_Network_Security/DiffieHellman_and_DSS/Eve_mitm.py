import socket
import MyDiffieHellman
import MyDSS

"""
Notes:
1. Can demonstrate the infiltration by using symmetric encryption like AES
"""

listening_port = 1500

s1 = socket.socket()
s1.bind(('', listening_port))
s1.listen(5)
print("Listening for incoming connections...")

c, addr = s1.accept()
print(f"Connected to Bob with the address: {addr}")

s2 = socket.socket()
s2.connect(('', 12345))
print("Connected to Alice on port 12345")

c, addr = s1.accept()
print(f"Connected to Bob with the address: {addr}")

print("With plain Diffie-Hellman:")
msg = c.recv(1024).decode()
p, g = [int(val) for val in msg.split()]
print(f"Received p and g from Bob: p={p}, g={g}")
s2.send(f"{p} {g}".encode())
print(f"Sent p and g to Alice: p={p}, g={g}")

msg = c.recv(1024).decode()
bob_public = int(msg)
print(f"Public key received from Bob: {bob_public}")

my_private1 = MyDiffieHellman.get_private_key(p)
my_public1 = MyDiffieHellman.get_public_key(g, my_private1, p)
print(f"My private key for Alice (not sent): {my_private1}")
print(f"My public key for Alice (sent): {my_public1}")
s2.send(str(my_public1).encode())

my_private2 = MyDiffieHellman.get_private_key(p)
my_public2 = MyDiffieHellman.get_public_key(g, my_private2, p)
print(f"My private key for Bob (not sent): {my_private2}")
print(f"My public key for Bob (sent): {my_public2}")
c.send(str(my_public2).encode())

shared_secret1 = MyDiffieHellman.get_shared_secret(bob_public, my_private1, p)
print(f"Shared secret with Alice: {shared_secret1}")
shared_secret2 = MyDiffieHellman.get_shared_secret(my_public1, my_private2, p)
print(f"Shared secret with Bob: {shared_secret2}")

print("Hence, I can intercept their messages.")

print()

print("Diffie-Hellman with DSS:")

# Continue from the Diffie-Hellman with DSS section
msg = c.recv(1024).decode()
p, g = [int(val) for val in msg.split()]
print(f"Received p and g from Bob: p={p}, g={g}")
s2.send(f"{p} {g}".encode())
print(f"Sent p and g to Alice: p={p}, g={g}")

msg = c.recv(1024).decode()
bob_public = int(msg)
print(f"Public key received from Bob: {bob_public}")

my_private1 = MyDiffieHellman.get_private_key(p)
my_public1 = MyDiffieHellman.get_public_key(g, my_private1, p)
print(f"My private key for Alice (not sent): {my_private1}")
print(f"My public key for Alice (sent): {my_public1}")
s2.send(str(my_public1).encode())

my_private2 = MyDiffieHellman.get_private_key(p)
my_public2 = MyDiffieHellman.get_public_key(g, my_private2, p)
print(f"My private key for Bob (not sent): {my_private2}")
print(f"My public key for Bob (sent): {my_public2}")
c.send(str(my_public2).encode())

shared_secret1 = MyDiffieHellman.get_shared_secret(bob_public, my_private1, p)
print(f"Shared secret with Alice: {shared_secret1}")
shared_secret2 = MyDiffieHellman.get_shared_secret(my_public1, my_private2, p)
print(f"Shared secret with Bob: {shared_secret2}")

# DSS Verification
msg = c.recv(1024).decode()
bob_identifier = msg
print(f"Identifier received from Bob: {bob_identifier}")

msg = c.recv(1024).decode()
bob_signature = tuple(map(int, msg.split()))
print(f"Signature received from Bob: {bob_signature}")

# Forward Bob's identifier and signature to Alice
s2.send(bob_identifier.encode())
s2.send(str(bob_signature).encode())

msg = s2.recv(1024).decode()
alice_identifier = msg
print(f"Identifier received from Alice: {alice_identifier}")

msg = s2.recv(1024).decode()
alice_signature = tuple(map(int, msg.split()))
print(f"Signature received from Alice: {alice_signature}")

# Forward Alice's identifier and signature to Bob
c.send(alice_identifier.encode())
c.send(str(alice_signature).encode())

# Attempt to verify signatures (will fail if DSS is implemented correctly)
print("Attempting to verify Bob's signature with Alice's DSS public key...")
verification = MyDSS.verify_signature(
    (alice_identifier, my_public1, bob_identifier, bob_public),
    bob_signature,
    my_public1
)
if not verification:
    print("Signature verification failed. DSS prevents MITM attack.")
else:
    print("Signature verification passed. MITM attack successful (unexpected).")
