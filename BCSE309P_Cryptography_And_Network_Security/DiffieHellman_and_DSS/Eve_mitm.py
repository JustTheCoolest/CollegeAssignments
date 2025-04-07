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
