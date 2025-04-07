import random
import math

def get_shared_initial_value():
    p = 23  # A prime number
    g = 5   # A primitive root modulo p
    return p, g

def get_private_key(p):
    return random.randint(1, p - 1)  # Private key should be in the range [1, p-1]

def get_public_key(g, private_key, p):
    return pow(g, private_key, p)  # Public key is g^private_key mod p

def get_shared_secret(public_key, private_key, p):
    return pow(public_key, private_key, p)  # Shared secret is public_key^private_key mod p

