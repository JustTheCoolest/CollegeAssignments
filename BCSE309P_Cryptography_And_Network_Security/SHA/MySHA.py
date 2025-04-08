"""
References:
1. Cryptography and Network Security, William Stallings
2. https://www.movable-type.co.uk/scripts/sha256.html
3. https://stepansnigirev.github.io/visual-sha256/
4. https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
"""

"""
Notes:
1. Manually tested for small string, but yet to be tested for strings greater than 1 block in size (it'll likely work)
"""

import math

def to_hex(num, NUM_SIZE):
    # Convert the number to a hexadecimal string and pad it to NUM_SIZE bytes
    hex_str = hex(num)[2:]  # Remove the '0x' prefix
    hex_str = hex_str.zfill(NUM_SIZE * 2)  # Pad to NUM_SIZE bytes (2 hex digits per byte)
    #print(len(hex_str), hex_str)
    assert len(hex_str) == NUM_SIZE * 2
    return hex_str

def rotr(n, x, NUM_SIZE):
    return ((x >> n) | (x << (NUM_SIZE * 8 - n))) % (2**(NUM_SIZE * 8))

def bigsig0(x, NUM_SIZE, params):
    return rotr(params[0], x, NUM_SIZE) ^ rotr(params[1], x, NUM_SIZE) ^ rotr(params[2], x, NUM_SIZE)

def bigsig1(x, NUM_SIZE, params):
    return rotr(params[0], x, NUM_SIZE) ^ rotr(params[1], x, NUM_SIZE) ^ rotr(params[2], x, NUM_SIZE)

def sig0(x, NUM_SIZE, params):
    return rotr(params[0], x, NUM_SIZE) ^ rotr(params[1], x, NUM_SIZE) ^ (x >> params[2])

def sig1(x, NUM_SIZE, params):
    return rotr(params[0], x, NUM_SIZE) ^ rotr(params[1], x, NUM_SIZE) ^ (x >> params[2])

def ch(x, y, z, NUM_SIZE):
    return (x & y) ^ (~x & z)

def maj(x, y, z, NUM_SIZE):
    return (x & y) ^ (x & z) ^ (y & z)

def sha(message, NUM_SIZE, NUM_ROUNDS, K, Hx, function_parameters):
    message += chr(0x80)
    num_blocks = math.ceil((len(message)+8)/16)
    mod_base = 2**(NUM_SIZE * 8)
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

    #print(blocks)

    for block in blocks:
        words = list(block)
        for x in range(16, NUM_ROUNDS):
            word = (sig1(words[x-2], NUM_SIZE, function_parameters['sig1']) + 
                    words[x-7] + 
                    sig0(words[x-15], NUM_SIZE, function_parameters['sig0']) + 
                    words[x-16]) % mod_base
            words.append(word)

        #print([to_hex(word, NUM_SIZE) for word in words])
        
        a, b, c, d, e, f, g, h = H
        for x in range(NUM_ROUNDS):
            T1 = (h + bigsig1(e, NUM_SIZE, function_parameters['bigsig1']) + 
                  ch(e, f, g, NUM_SIZE) + K[x] + words[x])
            T2 = bigsig0(a, NUM_SIZE, function_parameters['bigsig0']) + maj(a, b, c, NUM_SIZE)
            a, b, c, d, e, f, g, h = (T1+T2)%mod_base, a, b, c, (d+T1)%mod_base, e, f, g

        X = []
        for x, y in zip(H, (a, b, c, d, e, f, g, h)):
            X.append((x+y)%mod_base)
        H = X

    #print(H, len(H))
    assert len(H) == 8

    result = ""
    for comp in H:
        result += to_hex(comp, NUM_SIZE)

    assert len(result) == 8 * NUM_SIZE * 2

    return result

def sha256(message):
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

    function_parameters = {
        'bigsig0': (2, 13, 22),
        'bigsig1': (6, 11, 25),
        'sig0': (7, 18, 3),
        'sig1': (17, 19, 10),
    }

    return sha(message, 4, 64, K, Hx, function_parameters)

def sha512(message):
    # Constants for SHA-512
    K = [
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    ]
    # Initial hash values for SHA-512
    Hx = [
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    ]

    function_parameters = {
        'bigsig0': (28, 34, 39),
        'bigsig1': (14, 18, 41),
        'sig0': (1, 8, 7),
        'sig1': (19, 61, 6),
    }

    return sha(message, 8, 80, K, Hx, function_parameters)
