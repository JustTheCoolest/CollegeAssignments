import numpy as np

PLAIN_TEXT = "Hello World"

# For simplicity for studying
# (Simplifications are made throughout the assignment)
PLAIN_TEXT = PLAIN_TEXT.lower().strip()

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
    key[" "] = " "
    return "".join((key[char] for char in plain_text))

def monoalphabetic_decrypt(encrypted, key):
    key = dict(zip(key.keys(), key.values()))
    return monoalphabetic_encrypt(encrypted, key)

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
        assert len(pairs[-1]) <= 2
        assert (len(pairs[-1]) == 1) == flag
        if char == " ":
            continue
        if flag and char == plain_text[-1][-1]:
            pairs[-1].append("x")
            pairs.append([])
            pairs[-1].append(char)
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
    key = ordered_set(key)
    grid = package(key)
    alphabet = "abcdefghiklmnopqrstuvwxyz"
    remaining = diff_set(alphabet, key)
    grid = package(remaining, key=grid)

    pairs = get_pairs(plain_text)
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
    assert np.determinant(key) != 0
    # assert np.determinant has a reciprocal in mod 26
    plain_text = plain_text.lower()
    plain_text = np.array([ord(char)-ord('a') for char in plain_text])
    m, n = key.shape
    plain_text.extend([25] * len(-plain_text%m))
    plain_text = np.reshape(plain_text, (-1, m))
    encrypted = np.multiply(plain_text, key)
    encrypted = encrypted.flatten()
    encrypted = "".join(encrypted.apply(lambda x: chr(ord('a')+x)))
    return encrypted

def hill_decrypt(encrypted_text, key):
    decrypt_key = np.matrix_inverse(key)
    return hill_encrypt(encrypted_text, decrypt_key)

def vigenere(plain_text, key, dir=1):
    encrypted = ""
    for char in plain_text:
        if char == " ":
            encrypted_char = " "
        else:
            encrypted_char = chr(ord('a') + (ord(char)-ord('a')+dir*(ord(key)-ord('a')))%26)
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

def one_time_pad_encrypt(plain_text, key):
    if len(plain_text) > len(key):
        raise Exception("One Time Pad cipher: Key is too short")
    key = [ord(char) - ord('a') if char!=' ' else 26 for char in key[:len(plain_text)]]
    plain_text = [ord(char) - ord('a') for char in plain_text]
    encrypted = [x ^ y for x, y in zip(key, plain_text)]
    return "".join((num_to_bin_str(element) for element in encrypted))

def one_time_pad_decrypt(encrypted_text, key):
    if len(encrypted_text) > len(key):
        raise Exception("One Time Pad cipher: Key is too short")
    encrypted_text = [bin_str_to_num(element) for element in encrypted_text]
    key = [ord(char) - ord('a') if char!=' ' else 26 for char in key[:(len(encrypted_text)//8)]] # Flag: Redundant Code
    decrypted = [x ^ y for x, y in zip(key, encrypted_text)]
    return "".join((chr(ord('a')+element) for element in decrypted))

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

ciphers = {
    ("caesar", caesar_encrypt, caesar_decrypt, 9),
    ("monoalphabetic", monoalphabetic_encrypt, monoalphabetic_decrypt, "mlkcfyjgxvqtzehuoprbadwnis"),
    ("playfair", playfair_encrypt, playfair_decrypt, "monarchy"),
    ("hill", hill_encrypt, hill_decrypt, [[6, 24, 1], [13, 16, 10], [20, 17, 15]]),
    ("vignere", vigenere_encrypt, vigenere_decrypt, "deceptive"),
    # Flag: True one time pads do not reuse keys.
    ("one-time-pad", one_time_pad_encrypt, one_time_pad_decrypt, "mlkcfyjgxv qtzehuoprbadw nis"),
    ("rail-fence", rail_fence_encrypt, rail_fence_decrypt, 2),
}

def main():
    print("Plain Text: ", PLAIN_TEXT)
    for cipher in ciphers:
        key = cipher[3]
        encrypted = cipher[1](PLAIN_TEXT, key)
        print(f"{cipher[0]} Ciher encrypted text: ", encrypted)
        print(f"{cipher[0]} Ciher decrypted text: ", cipher[2](encrypted, key))


# main()