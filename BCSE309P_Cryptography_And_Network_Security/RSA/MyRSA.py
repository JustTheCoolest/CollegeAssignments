import random

"""
To be replaced:
1. Random number generator
2. Prime number generator
3. e generation?
4. Computational geometry for modular exponentiation
"""

def generate_primes():
    return 101, 97

def generate_e(phi):
    return 3

def mod_inv(a, n):
    x1, y1 = 1, 0
    x2, y2 = 0, 1

def mod_exp(v, a, n):
    return (v ** a) % n

def generate_key():
    p, q = generate_primes()
    phi = (p-1)*(q-1)
    n = p*q
    e = generate_e(phi)
    d = mod_inv(e, phi)
    return (n, e), (n, d)

def encrypt(text, key):
    text = [ord(char) for char in text]
    n, a = key
    def enc(v):
        return mod_exp(v, a, n)
    map(enc, text)
    text = [chr(char) for char in text]
    return "".join(text)

def decrypt(text, key):
    return encrypt(text, key)