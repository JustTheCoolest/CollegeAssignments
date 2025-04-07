import socket
import MyDiffieHellman
import MyElgamalDSS as MyDSS

port = 61500

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

# Receive DSS public key, Alice's public key, identifier, and signature
msg = s.recv(1024).decode()
dss_public, alice_public, alice_identifier, sign = eval(msg) 
print(f"Received DSS public key, Alice's public key, identifier, and signature: {dss_public}, {alice_public}, {alice_identifier}, {sign}")

# Verify Alice's signature
verification = MyDSS.verify_signature((alice_identifier, alice_public, get_my_addr(), bob_public), sign, dss_public)
if not verification:
    print("Signature verification failed.")
    print("Closing connection.")
    s.close()
else:
    print("Signature verification passed.")

# # Generate DSS keys for Bob
# dss_private, dss_public = MyDSS.get_keys()
# print(f"My DSS private key (not sent): {dss_private}")
# print(f"My DSS public key (sent): {dss_public}")

# # Sign the message to send to Alice
# bob_identifier = get_my_addr()
# sign = MyDSS.get_signature((bob_identifier, bob_public, alice_identifier, alice_public), dss_private, dss_public)

# # Send Bob's DSS public key, public key, identifier, and signature to Alice
# s.send(f"{bob_public} {sign[0]} {sign[1]}".encode())
# print(f"Sent Bob's DSS public key, public key, identifier, and signature: {bob_public}, {sign}")

# # Close the connection
# s.close()