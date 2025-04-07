import socket
import MyDiffieHellman
import MyElgamalDSS as MyDSS

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

print("With plain Diffie-Hellman:")
msg = c.recv(1024).decode()
p, g, bob_public = map(int, msg.split())
print(f"Received p, g, and public key from Bob: p={p}, g={g}, bob_public={bob_public}")

my_private1 = MyDiffieHellman.get_private_key(p)
my_public1 = MyDiffieHellman.get_public_key(g, my_private1, p)
print(f"My private key for Alice (not sent): {my_private1}")
print(f"My public key for Alice (sent): {my_public1}")

s2.send(f"{p} {g} {my_public1}".encode())
print(f"Sent p, g, and public key to Alice: p={p}, g={g}, public key for alice={my_public1}")

msg = s2.recv(1024).decode()
alice_public = int(msg)
print(f"Public key received from Alice: {alice_public}")

my_private2 = MyDiffieHellman.get_private_key(p)
my_public2 = MyDiffieHellman.get_public_key(g, my_private2, p)
print(f"My private key for Bob (not sent): {my_private2}")
print(f"My public key for Bob (sent): {my_public2}")
c.send(f"{my_public2}".encode())

shared_secret1 = MyDiffieHellman.get_shared_secret(alice_public, my_private1, p)
print(f"Shared secret with Alice: {shared_secret1}")
shared_secret2 = MyDiffieHellman.get_shared_secret(bob_public, my_private2, p)
print(f"Shared secret with Bob: {shared_secret2}")

print("Hence, I can intercept their messages.")

print()

print("Diffie-Hellman with DSS:")

msg = c.recv(1024).decode()
p, g, bob_public = map(int, msg.split())
print(f"Received p, g, and public key from Bob: p={p}, g={g}, bob_public={bob_public}")
s2.send(f"{p} {g} {bob_public}".encode())
print(f"Sent p, g, and public key to Alice: p={p}, g={g}, bob_public={bob_public}")

msg = c.recv(1024).decode()
bob_identifier, bob_signature = msg.rsplit(' ', 1)
bob_signature = tuple(map(int, bob_signature.split()))
print(f"Identifier and signature received from Bob: {bob_identifier}, {bob_signature}")

s2.send(f"{bob_identifier} {bob_signature}".encode())
msg = s2.recv(1024).decode()
alice_identifier, alice_signature = msg.rsplit(' ', 1)
alice_signature = tuple(map(int, alice_signature.split()))
print(f"Identifier and signature received from Alice: {alice_identifier}, {alice_signature}")

c.send(f"{alice_identifier} {alice_signature}".encode())

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
