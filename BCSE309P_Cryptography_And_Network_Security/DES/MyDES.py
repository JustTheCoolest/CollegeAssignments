"""
Notes:
1. This is only an academic implementation. This does not use proper bitarray implementations to be efficient in the real world.
2. References:
a. https://ziaullahrajpoot.medium.com/data-encryption-standard-des-dc8610aafdb3
b. https://csrc.nist.gov/files/pubs/fips/46-3/final/docs/fips46-3.pdf (FIPS PUB 46-3)
"""

def permute(bits, permutation):
    return [bits[i-1] for i in permutation]

def generate_key(seed):
    key = [0] * 64
    for i in range(64):
        seed = (16807 * seed) % 2147483647 # Linear Congruential Generator
        key[i] = seed % 2
    return key

def next_key(key, round_number):
    pass

def substitute(bits, sbox_number):
    s_boxes = [
    # S-box 1
    [
        [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
        [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
        [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
        [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]
    ],
    # S-box 2
    [
        [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
        [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
        [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
        [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]
    ],
    # S-box 3
    [
        [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
        [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
        [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
        [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]
    ],
    # S-box 4
    [
        [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
        [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
        [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
        [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]
    ],
    # S-box 5
    [
        [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
        [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
        [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
        [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]
    ],
    # S-box 6
    [
        [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
        [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
        [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
        [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]
    ],
    # S-box 7
    [
        [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
        [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
        [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
        [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]
    ],
    # S-box 8
    [
        [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
        [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
        [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
        [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]
    ]
    ]

    row = bits[0] * 2 + bits[-1]
    column = int(''.join(str(bit) for bit in bits[1:-1]), 2)
    val = s_boxes[sbox_number][row][column]
    return [int(bit) for bit in format(val, '04b')]

def f(right, key):
    EP = [
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
    ]

    P = [
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
    ]

    right = permute(right, EP)
    right = [right[i] ^ key[i] for i in range(48)]
    new_right = []
    for i in range(8):
        new_right += substitute(right[i*6:(i+1)*6], i)
    new_right = permute(new_right, P)
    return new_right

def round(left, right, key):
    return right, [left[i] ^ x for i, x in enumerate(f(right, key))]

def DES(bits, keys):
    IP = [
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
    ]

    IP_INV = [
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
    ]

    bits = permute(bits, IP)
    left, right = bits[:32], bits[32:]
    for i in range(16):
        key = keys[i]
        left, right = round(left, right, key)
    bits = right + left
    bits = permute(bits, IP_INV)
    return bits

def get_bitlist_from_text(text):
    text = text + "\0" * (8 - len(text))
    bitstring = ''.join(format(ord(c), '08b') for c in text)
    assert set(bitstring) <= {'0', '1'}
    return [int(bit) for bit in bitstring]

def get_bitstring_from_bitlist(bitlist):
    assert set(bitlist) <= {0, 1}
    return ''.join(str(bit) for bit in bitlist)

def get_bitlist_from_bitstring(bitstring):
    assert set(bitstring) <= {'0', '1'}
    return [int(bit) for bit in bitstring]

def get_text_from_bitlist(bitlist):
    assert set(bitlist) <= {0, 1}
    bitstring = ''.join(str(bit) for bit in bitlist)
    text = ''.join(chr(int(bitstring[i:i+8], 2)) for i in range(0, len(bitstring), 8))
    return text.rstrip('\0')

def circular_shift(bits, shift):
    return bits[shift:] + bits[:shift]

def generate_keys(seed):
    PC1 = [
    57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15, 7, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37,
    29, 21, 13, 5, 28, 20, 12, 4
    ]

    PC2 = [
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
    ]

    shift_schedule = [
        1, 1, 2, 2,
        2, 2, 2, 2,
        1, 2, 2, 2,
        2, 2, 2, 1
    ]

    keys = []
    key = generate_key(seed)
    key = permute(key, PC1)
    left, right = key[:28], key[28:]
    for i in range(16):
        left = circular_shift(left, shift_schedule[i])
        right = circular_shift(right, shift_schedule[i])
        keys.append(permute(left + right, PC2))
    return keys

def process_text(text, seed, block_size, process_function, convert_input, convert_output):
    result = ""
    for i in range(0, len(text), block_size):
        bits = convert_input(text[i:i+block_size])
        bits = process_function(bits)
        result += convert_output(bits)
    return result

def encrypt(text, seed):
    keys = generate_keys(seed)
    process_function = lambda x : DES(x, keys)
    return process_text(text, seed, 8, process_function, get_bitlist_from_text, get_bitstring_from_bitlist)

def decrypt(text, seed):
    keys = generate_keys(seed)[::-1]
    process_function = lambda x : DES(x, keys)
    return process_text(text, seed, 64, process_function, get_bitlist_from_bitstring, get_text_from_bitlist)