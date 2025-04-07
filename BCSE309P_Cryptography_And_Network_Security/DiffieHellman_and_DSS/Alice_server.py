import socket
import MyDiffieHellman
import MyElgamalDSS as MyDSS

port = 12345

def get_my_addr():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return (ip_address, port)

s = socket.socket()
s.bind(('', port))
s.listen(5)

print("With plain Diffie-Hellman:")

c, addr = s.accept()
print(f"Connected to client with the address: {addr}")

msg = c.recv(1024).decode()
p, g, cpublic = map(int, msg.split())
print(f"Received p, g, and public key from client: p={p}, g={g}, cpublic={cpublic}")

my_private = MyDiffieHellman.get_private_key(p)
my_public = MyDiffieHellman.get_public_key(g, my_private, p)
print(f"My private key (not sent): {my_private}")
c.send(f"{my_public}".encode())
print(f"My public key (sent): {my_public}")

shared_secret = MyDiffieHellman.get_shared_secret(cpublic, my_private, p)
print(f"Shared secret: {shared_secret}")

print()

print("Diffie-Hellman with DSS:")

msg = c.recv(1024).decode()
p, g, cpublic = map(int, msg.split())
print(f"Received p, g, and public key from client: p={p}, g={g}, cpublic={cpublic}")
print(f"Identifier of the client: {addr}")

dss_private, dss_public = MyDSS.get_keys()
print(f"My DSS private key (not sent): {dss_private}")
my_private = MyDiffieHellman.get_private_key(p)
my_public = MyDiffieHellman.get_public_key(g, my_private, p)
my_identifier = get_my_addr()
sign = MyDSS.get_signature((addr, cpublic, my_identifier, my_public), dss_private, dss_public)

c.send(f"{dss_public}, {my_public}, {my_identifier}, {sign}".encode())
print(f"My DSS public key, public key, identifier, and signature (sent): {dss_public}, {my_public}, {my_identifier}, {sign}")

# msg = c.recv(1024).decode()
# msg, sign = msg.rsplit(' ', 1)
# msg = int(msg)
# sign = tuple(map(int, sign.split()))
# print(f"Public key and signature received from client: {msg}, {sign}")

# verification = MyDSS.verify_signature((my_identifier, my_public, addr, cpublic), sign, dss_public)

# if not verification:
#     print("Signature verification failed.")
#     print("Closing connection.")
# else:
#     raise RuntimeError("Unhandled case: Signature verification passed.")
