import socket
import MyDiffieHellman
import MyElgamalDSS as MyDSS

"""
Notes:
1. Can demonstrate the infiltration by using symmetric encryption like AES
2. For the DSS part, MITM some steps were skipped, because signature verification will fail anyway (it's just demonstratiion)
3. A more faithful MITM would be needed to correctly demonstrate the DSS security
"""

listening_port = 61500

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

# Receive DSS public key, Alice's public key, identifier, and signature
msg = s2.recv(1024).decode()
dss_public, alice_public, alice_identifier, sign = eval(msg)
print(f"Received DSS public key, Alice's public key, identifier, and signature: {dss_public}, {alice_public}, {alice_identifier}, {sign}")

# Forward DSS public key, Alice's public key, identifier, and signature to Bob
c.send(f"{dss_public}, {alice_public}, {alice_identifier}, {(sign[0], sign[1])}".encode())
print(f"Forwarded DSS public key, Alice's public key, identifier, and signature to Bob.")

# # Receive Bob's DSS public key, public key, identifier, and signature
# msg = c.recv(1024).decode()
# bob_dss_public, bob_public, bob_identifier, bob_sign = msg.split(' ', 3)
# bob_dss_public = int(bob_dss_public)
# bob_public = int(bob_public)
# bob_identifier = eval(bob_identifier)  # Convert string back to tuple
# bob_sign = tuple(map(int, bob_sign.split()))
# print(f"Received Bob's DSS public key, public key, identifier, and signature: {bob_dss_public}, {bob_public}, {bob_identifier}, {bob_sign}")

# # Forward Bob's DSS public key, public key, identifier, and signature to Alice
# s2.send(f"{bob_dss_public} {bob_public} {bob_identifier} {bob_sign[0]} {bob_sign[1]}".encode())
# print(f"Forwarded Bob's DSS public key, public key, identifier, and signature to Alice.")

# # Close connections
# c.close()
# s2.close()
# print("MITM attack completed.")