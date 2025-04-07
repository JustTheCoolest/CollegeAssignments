import socket
import MyDiffieHellman
import MyElgmalDSS as MyDSS

port = 12345

def get_my_addr(s):
    hostname = socket.gethostname(s)
    ip_address = socket.gethostbyname(hostname)
    return (ip_address, port)

s = socket.socket()
s.bind(('', port))
s.listen(5)

print("With plain Diffie-Hellman:")

c, addr = s.accept()
print(f"Connected to client with the address: {addr}")

msg = c.recv(1024).decode()
p, g = [int(val) for val in msg.split()]
print(f"Received p and g from client: p={p}, g={g}")

msg = c.recv(1024).decode()
cpublic = int(msg)
print(f"Public key received from client: {cpublic}")

my_private = MyDiffieHellman.get_private_key(p)
my_public = MyDiffieHellman.get_public_key(g, my_private, p)
print(f"My private key (not sent): {my_private}")
print(f"My public key (sent): {my_public}")
c.send(str(my_public).encode())

shared_secret = MyDiffieHellman.get_shared_secret(cpublic, my_private, p)
print(f"Shared secret: {shared_secret}")

print()

print("Diffie-Hellman with DSS:")

msg = c.recv(1024).decode()
p, g = [int(val) for val in msg.split()]
print(f"Received p and g from client: p={p}, g={g}")

msg = c.recv(1024).decode()
cpublic = int(msg)
print(f"Public key received from client: {cpublic}")
print(f"Identifier of the client: {addr}")

dss_private, dss_public = MyDSS.get_keys()
print(f"My DSS private key (not sent): {dss_private}")
print(f"My DSS public key (sent): {dss_public}")
c.send(str(dss_public).encode())

my_private = MyDiffieHellman.get_private_key(p)
my_public = MyDiffieHellman.get_public_key(g, my_private, p)
print(f"My private key (not sent): {my_private}")
print(f"My public key (sent): {my_public}")
c.send(str(my_public).encode())

my_identifier = get_my_addr()
print(f"My identifier (sent): {my_identifier}")
c.send(my_identifier.encode())

sign = MyDSS.get_signature((addr, cpublic, my_identifier, my_public)) # Flag
print(f"Signature (sent): {sign}")
c.send(str(sign).encode())

msg = c.recv(1024).decode()
msg = int(msg)
print(f"Public key received from client: {msg}")
print(f"Identifier of the client: {addr}")

msg = c.recv(1024).decode()
sign = tuple(map(int, msg.split()))
print(f"Signature received from client: {sign}")

verification = MyDSS.verify_signature((my_identifier, my_public, addr, cpublic), sign, dss_public)

if not verification:
    print("Signature verification failed.")
    print("Closing connection.")
    # c.send("SIGNATURE_VERIFICATION_FAILED".encode())
else:
    raise RuntimeError("Unhandled case: Signature verification passed.")
