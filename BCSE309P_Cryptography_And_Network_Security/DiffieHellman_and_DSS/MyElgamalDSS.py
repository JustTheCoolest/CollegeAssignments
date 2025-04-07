"""
Notes:
1. A better hash function like SHA can be used
"""

import random
import math

from MyDiffieHellman import get_shared_initial_value, get_private_key, get_public_key

def get_keys():
    p, g = get_shared_initial_value()
    private_key = get_private_key(p)
    public_key = get_public_key(g, private_key, p)
    public_key = (p, g, public_key)
    return private_key, public_key

def mod_inv(a, n):
    """ Assuming it exists """
    # Flag: e generation and d generation can be done at once
    # Flag: Alternate implementation algorithms can be explored for a potential speed up
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

def get_hash(message):
    return message.__hash__()

def get_signature(message, private_key, public_key):
    p, g, _ = public_key
    m = get_hash(message)
    K = random.randint(1, p - 1)  # Random integer in the range [1, p-1]
    S1 = pow(g, K, p)  # S1 = g^K mod p
    K_inv = mod_inv(K, p - 1)  # K^-1 mod (p-1)
    S2 = (K_inv * (m - private_key * S1)) % (p - 1)  # S2 = K^-1 * (m - d * S1) mod (p-1)
    return S1, S2

def verify_signature(message, signature, public_key):
    p, g, y = public_key
    m = get_hash(message)
    S1, S2 = signature
    if S1 < 1 or S1 > p - 1 or S2 < 1 or S2 > p - 1:
        return False
    V1 = pow(g, m, p)  # V1 = g^m mod p
    V2 = (pow(y, S1, p) * pow(S1, S2, p)) % p  # V2 = (y^S1 * S1^S2) mod p
    return V1 == V2  # Return True if V1 == V2, else False