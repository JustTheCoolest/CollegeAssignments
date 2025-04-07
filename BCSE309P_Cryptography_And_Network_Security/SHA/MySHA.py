import math

# Constants for SHA-256
K = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
]

# Initial hash values for SHA-256
Hx = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
]
def to_hex(num, NUM_SIZE):
    # Convert the number to a hexadecimal string and pad it to NUM_SIZE bytes
    hex_str = hex(num)[2:]  # Remove the '0x' prefix
    hex_str = hex_str.zfill(NUM_SIZE * 2)  # Pad to NUM_SIZE bytes (2 hex digits per byte)
    print(len(hex_str), hex_str)
    assert len(hex_str) == NUM_SIZE * 2
    return hex_str

def rotr(n, x, NUM_SIZE):
    return ((x >> n) | (x << (NUM_SIZE * 8 - n))) % (2**(NUM_SIZE * 8))

def bigsig0(x, NUM_SIZE):
    return rotr(2, x, NUM_SIZE) ^ rotr(13, x, NUM_SIZE) ^ rotr(22, x, NUM_SIZE)

def bigsig1(x, NUM_SIZE):
    return rotr(6, x, NUM_SIZE) ^ rotr(11, x, NUM_SIZE) ^ rotr(25, x, NUM_SIZE)

def sig0(x, NUM_SIZE):
    return rotr(7, x, NUM_SIZE) ^ rotr(18, x, NUM_SIZE) ^ (x >> 3)

def sig1(x, NUM_SIZE):
    return rotr(17, x, NUM_SIZE) ^ rotr(19, x, NUM_SIZE) ^ (x >> 10)

def ch(x, y, z, NUM_SIZE):
    return (x & y) ^ (~x & z)

def maj(x, y, z, NUM_SIZE):
    return (x & y) ^ (x & z) ^ (y & z)

def sha(message, NUM_SIZE, NUM_ROUNDS):
    message += chr(0x80)
    num_blocks = math.ceil((len(message)+8)/16)
    mod_base = 2**(NUM_SIZE * 16)
    H = Hx.copy()
    blocks = []
    for x in range(num_blocks):

        block_base = x * 16 * NUM_SIZE
        block = []
        for y in range(16):
            chunk_base = block_base + y * NUM_SIZE
            num = 0
            for z in range(NUM_SIZE):
                curr_index = chunk_base + z
                curr = ord(message[curr_index]) if curr_index < len(message) else 0
                num <<= 8
                num += curr
                assert curr < 2**8
            block.append(num)
        blocks.append(block)
        # Flag: Using a multi-pass solution at the expense of higher memory complexity, for code simplicity

    size = (len(message) - 1) * 8
    blocks[-1][-1] = size % mod_base # Flag: Ignoring Python's lack of compile phase optimisations
    blocks[-1][-2] = size // mod_base
    assert blocks[-1][-2] < mod_base

    print(blocks)

    for block in blocks:
        words = list(block)
        for x in range(16, NUM_ROUNDS):
            word = (sig1(words[x-2], NUM_SIZE) + words[x-7] + sig0(words[x-15], NUM_SIZE) + words[x-16]) % mod_base
            words.append(word)

        print(words)
        
        a, b, c, d, e, f, g, h = H
        for x in range(NUM_ROUNDS):
            T1 = h + bigsig1(e, NUM_SIZE) + ch(e, f, g, NUM_SIZE) + K[x] + words[x]
            T2 = bigsig0(a, NUM_SIZE) + maj(a, b, c, NUM_SIZE)
            a, b, c, d, e, f, g, h = (T1+T2)%mod_base, a, b, c, (d+T1)%mod_base, e, f, g

        X = []
        for x, y in zip(H, (a, b, c, d, e, f, g, h)):
            X.append((x+y)%mod_base)
        H = X

    print(H, len(H))
    assert len(H) == 8

    result = ""
    for comp in H:
        result += to_hex(comp, NUM_SIZE)

    assert len(result) == 8 * NUM_SIZE * 2

    return result

def sha256(message):
    return sha(message, 4, 64)

def sha512(message):
    return sha(message, 8, 80)
