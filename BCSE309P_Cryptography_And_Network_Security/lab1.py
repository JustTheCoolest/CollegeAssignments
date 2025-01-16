import numpy as np

PLAIN_TEXT = "Hello World"

"""
Architecture suggestions:
Instead of storing keys as direct objects, store them as functions that have to be called. 
This way any key generation process (including having to send the key to the other party) can be done in the key generation function.
"""

# For simplicity for studying
# (Simplifications are made throughout the assignment)
PLAIN_TEXT = PLAIN_TEXT.lower().strip()

ALPHABET = "abcdefghijklmnopqrstuvwxyz"

def caesar_encrypt(plain_text, key):
    encrypted = ""
    for character in plain_text:
        if character == " ":
            encrypted_char = " "
        else:
            encrypted_char = chr(ord('a') + (ord(character)-ord('a')+key)%26)
        encrypted += encrypted_char
    return encrypted

def caesar_decrypt(encrypted, key):
    return caesar_encrypt(encrypted, -key)

def monoalphabetic_encrypt(plain_text, key):
    key = dict(zip(ALPHABET, key))
    key[" "] = " "
    return "".join((key[char] for char in plain_text))

def monoalphabetic_decrypt(encrypted, key):
    key = dict(zip(key, ALPHABET))
    key[" "] = " "
    return "".join((key[char] for char in encrypted)) # Flag: Redundant Code

# Monoalphabetic Cipher key generation:

# import numpy

# alphabet = list((chr(ord('a')+i) for i in range(26)))

# copy =list(alphabet)

# # print(alphabet)

# numpy.random.shuffle(alphabet)
# # print(alphabet)

# # print(dict(zip(copy, alphabet)))

# print("".join(alphabet))

def ordered_set(key):
    result = []
    for char in key:
        if char in result:
            continue
        result.append(char)
    return result

def package(remaining, key=None):
    if key is None:
        grid = [[]]
    else:
        grid = key
    for char in remaining:
        if len(grid[-1]) == 5:
            grid.append([])
        grid[-1].append(char)
    return grid

def diff_set(alphabet, key):
    return [letter for letter in alphabet if letter not in key]

def get_pairs(plain_text, filler="x"):
    pairs = []
    flag = False
    for char in plain_text:
        # print(pairs, char, flag)
        assert len(pairs)==0 or len(pairs[-1]) <= 2
        assert len(pairs)==0 or (len(pairs[-1]) == 1) == flag
        if char == " ":
            continue
        if flag and (char == pairs[-1][-1]):
            pairs[-1].append("x")
            pairs.append([])
            pairs[-1].append(char)
            continue
        if flag:
            pairs[-1].append(char)
            flag = False
        else:
            pairs.append([])
            pairs[-1].append(char)
            flag = True
    if flag:
        pairs[-1].append("x")
    assert len(pairs)==0 or len(pairs[-1]) == 2
    return pairs

def get_position(char, grid):
    # Improvement: Hashing
    for i in range(5):
        for j in range(5):
            if grid[i][j] == char:
                return i, j

def join_pairs(pairs):
    return "".join((pair[0]+pair[1] for pair in pairs))

def playfair(plain_text, key, dir):
    plain_text = plain_text.replace("j", "i")
    key = ordered_set(key)
    grid = package(key)
    alphabet = "abcdefghiklmnopqrstuvwxyz"
    remaining = diff_set(alphabet, key)
    grid = package(remaining, key=grid)
    # print(grid)

    pairs = get_pairs(plain_text)
    # print(pairs)
    for pair in pairs:
        p1 = get_position(pair[0], grid)
        p2 = get_position(pair[1], grid)
        if p1[0] == p2[0]:
            pair[0] = grid[p1[0]][(p1[1]+dir)%5]
            pair[1] = grid[p2[0]][(p2[1]+dir)%5]
        elif p1[1] == p2[1]:
            pair[0] = grid[(p1[0]+dir)%5][p1[1]]
            pair[1] = grid[(p2[0]+dir)%5][p2[1]]
        else:
            pair[0] = grid[p1[0]][p2[1]]
            pair[1] = grid[p2[0]][p1[1]]

    return join_pairs(pairs)

def playfair_encrypt(plain_text, key):
    return playfair(plain_text, key, 1)

def playfair_decrypt(encrypted, key):
    return playfair(encrypted, key, -1)

def hill_encrypt(plain_text, key, filler=25):
    # assert np.determinant(key) != 0
    # assert np.determinant has a reciprocal in mod 26
    plain_text = plain_text.lower().replace(" ", "")
    plain_text = np.array([ord(char)-ord('a') for char in plain_text], dtype=int)
    key = np.array(key, dtype=int)
    m, n = key.shape
    plain_text = np.append(plain_text, [25] * ((-len(plain_text)) % m))
    plain_text = np.reshape(plain_text, (-1, m))
    plain_text = np.array(plain_text, dtype=int)
    encrypted = plain_text @ key
    # print(plain_text.dtype, key.dtype, encrypted.dtype)
    encrypted = encrypted % 26
    encrypted = encrypted.flatten()
    # Flag: Vectorize
    encrypted = "".join([chr(ord('a') + x) for x in encrypted])
    return encrypted

def adj_transp(key):
    # Flag: Implementing only for 2x2 matrices
    a, b, c, d = key[0][0], key[0][1], key[1][0], key[1][1]
    return [[d, -b], [-c, a]]

def modular_inverse_element(det, mod=26):
    if mod != 26:
        raise Exception("Only mod 26 is supported")
    mapping = {
        1: 1,
        3: 9,
        5: 21,
        7: 15,
        9: 3,
        11: 19,
        15: 7,
        17: 23,
        19: 11,
        21: 5,
        23: 17,
        25: 25
    }
    # print(det)
    det %= mod
    # print(det)
    if det not in mapping:
        raise Exception("The determinant of this matrix does not have an inverse under mod 26")
    return mapping[det]

def modular_inverse(key, det, mod=26):
    key = np.array(key, dtype=int)
    multiplier = modular_inverse_element(det, mod)
    key = key * multiplier
    return key

def determinant(key):
    # Flag: Implementing only for 2x2 matrices
    a, b, c, d = key[0][0], key[0][1], key[1][0], key[1][1]
    return a*d - b*c

def hill_decrypt(encrypted_text, key):
    # Flag: Implementing only for 2x2 matrices
    key = np.array(key, dtype=int)
    det = determinant(key)
    key = adj_transp(key)
    key = modular_inverse(key, det)
    return hill_encrypt(encrypted_text, key)

def vigenere(plain_text, key, dir=1):
    n = len(key)
    encrypted = ""
    for i, char in enumerate(plain_text):
        if char == " ":
            encrypted_char = " "
        else:
            encrypted_char = chr(ord('a') + (ord(char)-ord('a')+dir*(ord(key[i%n])-ord('a')))%26)
        encrypted += encrypted_char
    return encrypted

def vigenere_encrypt(plain_text, key):
    return vigenere(plain_text, key, 1)

def vigenere_decrypt(encrypted_text, key):
    return vigenere(encrypted_text, key, -1)

def num_to_bin_str(num):
    # return bin(num)[2:].zfill(8)
    # (reimplementing manually)
    result = ""
    while num > 0:
        result = str(num%2) + result
        num = num//2
    assert len(result) <= 8
    return "0"*(8-len(result)) + result

def bin_str_to_num(bin_str):
    result = 0
    for i in range(8):
        result = result*2 + int(bin_str[i])
        # Flag: Not parallelizable
    return result

def spaceful_encode(plain_text):
    # Flag: Redundant Code in other places
    return [ord(char) - ord('a') if char!=' ' else 26 for char in plain_text]

def one_time_pad_encrypt(plain_text, key):
    if len(plain_text) > len(key):
        raise Exception("One Time Pad cipher: Key is too short")
    key = [ord(char) - ord('a') if char!=' ' else 26 for char in key[:len(plain_text)]]
    plain_text = spaceful_encode(plain_text)
    encrypted = [x ^ y for x, y in zip(key, plain_text)]
    return "".join((num_to_bin_str(element) for element in encrypted))

def one_time_pad_decrypt(encrypted_text, key):
    encrypted_text = [encrypted_text[i:i+8] for i in range(0, len(encrypted_text), 8)]
    encrypted_text = [bin_str_to_num(element) for element in encrypted_text]
    if len(encrypted_text) > len(key):
        raise Exception("One Time Pad cipher: Key is too short")
    key = [ord(char) - ord('a') if char!=' ' else 26 for char in key[:len(encrypted_text)]] # Flag: Redundant Code
    # print(key)
    # print(encrypted_text)
    decrypted = [x^y for x, y in zip(key, encrypted_text)]
    # print(decrypted)
    return "".join((chr(ord('a')+element) if element != 26 else ' ' for element in decrypted))

def rail_fence_encrypt(plain_text, depth=2):
    encrypted = ""
    for i in range(depth):
        encrypted += plain_text[i::depth]
    return encrypted

def rail_fence_decrypt(encrypted_text, depth=2):
    n = len(encrypted_text)//depth
    r = len(encrypted_text)%depth
    decrypted = ""
    starts = []
    starts.extend([x for x in range(0, r*(n+1), n+1)])  
    starts.extend([x for x in range(r*(n+1), len(encrypted_text), n)])
    for i in range(n):
        for start in starts:
            decrypted += encrypted_text[start+i]
    for i in range(r):
        decrypted += encrypted_text[starts[i]+n]
    return decrypted

ciphers = [
    ("caesar", caesar_encrypt, caesar_decrypt, 9),
    ("monoalphabetic", monoalphabetic_encrypt, monoalphabetic_decrypt, "mlkcfyjgxvqtzehuoprbadwnis"),
    ("playfair", playfair_encrypt, playfair_decrypt, "monarchy"),
    # ("hill", hill_encrypt, hill_decrypt, ((6, 24, 1), (13, 16, 10), (20, 17, 15))),
    ("hill", hill_encrypt, hill_decrypt, ((5, 8), (17, 3))),
    ("vignere", vigenere_encrypt, vigenere_decrypt, "deceptive"),
    # Flag: True one time pads do not reuse keys.
    ("one-time-pad", one_time_pad_encrypt, one_time_pad_decrypt, "mlkcfyjgxv qtzehuoprbadw nis"),
    ("rail-fence", rail_fence_encrypt, rail_fence_decrypt, 2),
]

def main():
    print("Plain Text: ", PLAIN_TEXT)
    for cipher in ciphers:
        key = cipher[3]
        encrypted = cipher[1](PLAIN_TEXT, key)
        print(f"{cipher[0]} Ciher encrypted text: ", encrypted)
        print(f"{cipher[0]} Ciher decrypted text: ", cipher[2](encrypted, key))

if __name__ == "__main__":
    main()