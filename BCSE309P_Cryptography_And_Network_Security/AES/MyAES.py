"""
Citations:
1. https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf
2. https://cs.ru.nl/~joan/papers/JDA_VRI_Rijndael_2002.pdf 
3. https://github.com/bozhu/AES-Python/blob/master/aes.py
4. Cryptography and Network Security by William Stallings
"""

"""
Notes:
1. The key can be generated on the go, to reduce memory complexity
2. Pre compute the S-box and inverse S-box (code can be written to generate them, but I haven't done it)
"""

import random

KEY = "Thats my Kung Fu"
KEY = [ord(c) for c in KEY]

s_box = (
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
)

inv_sbox = (
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
)

rcon = (
    0x00,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36
)

def generate_key(prev_key, i):
    last_word = prev_key[3]
    last_word = last_word[1:] + last_word[:1]
    last_word = [s_box[b] for b in last_word]
    last_word[0] = last_word[0] ^ rcon[i]
    new_key = []
    for j in range(4):
        new_word = []
        for k in range(4):
            new_word.append(prev_key[j][k] ^ last_word[k])
        new_key.append(new_word)
        last_word = new_word
    return new_key

def generate_keys(key):
    key = [key[i:i + 4] for i in range(0, len(key), 4)]
    keys = []
    keys.append(key)
    for i in range(1, 11):
        keys.append(generate_key(keys[i - 1], i))
    return keys

def add_round_key(text, key):
    # print(text, key)
    for i in range(4):
        for j in range(4):
            text[i][j] = text[i][j] ^ key[i][j]
    return text

def sub_bytes(text):
    for i in range(4):
        for j in range(4):
            text[i][j] = s_box[text[i][j]]
    return text

def inv_sub_bytes(text):
    for i in range(4):
        for j in range(4):
            text[i][j] = inv_sbox[text[i][j]]
    return text

def shift_rows(text):
    for i in range(4):
        text[i] = text[i][i:] + text[i][:i]
    return text

def inv_shift_rows(text):
    for i in range(4):
        text[i] = text[i][4 - i:] + text[i][:4 - i]
    return text


# Flag: Yet to study proof. This is Rijndael's Galois Field multiplication

xtime = lambda a: (((a << 1) ^ 0x1B) & 0xFF) if (a & 0x80) else (a << 1)

def mix_column(column):
    a = column
    t = a[0] ^ a[1] ^ a[2] ^ a[3]
    u = a[0]
    a[0] ^= t ^ xtime(a[0] ^ a[1])
    a[1] ^= t ^ xtime(a[1] ^ a[2])
    a[2] ^= t ^ xtime(a[2] ^ a[3])
    a[3] ^= t ^ xtime(a[3] ^ u)
    return column

def mix_columns(text):
    for i in range(4):
        a = text[0][i]
        b = text[1][i]
        c = text[2][i]
        d = text[3][i]
        column = [a, b, c, d]
        column = mix_column(column)
        a, b, c, d = column
        text[0][i] = a
        text[1][i] = b
        text[2][i] = c
        text[3][i] = d
    return text

def inv_mix_columns(text):
    for i in range(4):
        a = text[0][i]
        b = text[1][i]
        c = text[2][i]
        d = text[3][i]
        u = xtime(xtime(a ^ c))
        v = xtime(xtime(b ^ d))
        text[0][i] = a ^ u
        text[1][i] = b ^ v
        text[2][i] = c ^ u
        text[3][i] = d ^ v
    return text

def get_matrix_from_chars(text):
    if len(text) > 16:
        raise Exception("Text length should be less than 16 for this implementation")
    text = text + "\0" * (16 - len(text))
    matrix = []
    for i in range(0, len(text), 4):
        matrix.append([ord(text[i]), ord(text[i + 1]), ord(text[i + 2]), ord(text[i + 3])])
    return matrix

def get_chars_from_matrix(matrix):
    text = ""
    for i in range(4):
        for j in range(4):
            text += chr(matrix[i][j])
    return text

def encrypt(text, key):
    text = get_matrix_from_chars(text)
    keys = generate_keys(key)
    text = add_round_key(text, keys[0])
    for i in range(1, 10):
        text = sub_bytes(text)
        text = shift_rows(text)
        # text = mix_columns(text)
        text = add_round_key(text, keys[i])
    text = sub_bytes(text)
    text = shift_rows(text)
    text = add_round_key(text, keys[10])
    return get_chars_from_matrix(text)

def decrypt(text, key):
    text = get_matrix_from_chars(text)
    keys = generate_keys(key)
    text = add_round_key(text, keys[10])
    text = inv_shift_rows(text)
    text = inv_sub_bytes(text)
    for i in range(9, 0, -1):
        text = add_round_key(text, keys[i])
        # text = inv_mix_columns(text)
        text = inv_shift_rows(text)
        text = inv_sub_bytes(text)
    text = add_round_key(text, keys[0])
    return get_chars_from_matrix(text)


