import random

"""
To be replaced:
1. Random number generator
2. Prime number generator
3. e generation?
4. Computational geometry for modular exponentiation
"""

e_iterator = 0

def generate_primes():
    return 101, 97
    # return 5, 7

def generate_e(phi):
    global e_iterator
    vals = [3, 7, 11]
    if vals[e_iterator] > phi:
        e_iterator = 0
    result = vals[e_iterator]
    e_iterator += 1
    return result

def mod_inv(a, n):
    """ Assuming it exists """
    # Flag: e generation and d generation can be done at once
    # print(a, n)
    x1, y1 = 1, 0
    x2, y2 = 0, 1
    og_a = a
    og_n = n
    a, b = n, a
    def step_multipliers(z1, z2, q):
        return z2, z1 - q * z2
    r = a % b
    # if r==0:
    #     return -1
    while r != 0:
        q = a//b
        r = a%b
        x1, x2 = step_multipliers(x1, x2, q)
        y1, y2 = step_multipliers(y1, y2, q)
        # print(f"{a} = {q} * {b} + {r}; {r} = {x2} * {og_n} + {y2} * {og_a}")
        a, b = b, r
    if a != 1:
        return -1
    result = y1 % og_n
    # print(result)
    return result

def mod_exp(v, a, n):
    # return (v ** a) % n
    return pow(v, a, mod=n)

def generate_key():
    p, q = generate_primes()
    phi = (p-1)*(q-1)
    n = p*q
    for i in range(2): # max_tries = 2
        e = generate_e(phi)
        d = mod_inv(e, phi)
        if d!=-1:
            break
    else:
        raise RuntimeError(f"Could not find a primitive root with an inverse under base phi = {phi}, from the premade set of e")
    assert (e*d)%phi == 1
    return (n, d), (n, e)

def encrypt(text, key):
    text = [ord(char) for char in text]
    n, a = key
    def enc(v):
        return mod_exp(v, a, n)
    text = map(enc, text)
    text = [chr(char) for char in text]
    result = "".join(text)
    # print(f"Encryptor's log: {result}")
    return result

def decrypt(text, key):
    return encrypt(text, key)