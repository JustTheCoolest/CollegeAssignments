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

def playfair_encrypt(plain_text, key):
    key = ordered_set(key)
    grid = package(key)
    remaining = ordered_set(alphabet) - key
    grid = package(remaining, key=grid)
    

ciphers = {
    ("caesar", caesar_encrypt, caesar_decrypt, 9),
    ("monoalphabetic", monoalphabetic_encrypt, monoalphabetic_decrypt, "mlkcfyjgxvqtzehuoprbadwnis"),
    # ("playfair", playfair_encrypt, playfair_decrypt),
}

def main():
    print("Plain Text: ", PLAIN_TEXT)
    for cipher in ciphers:
        key = cipher[3]
        encrypted = cipher[1](PLAIN_TEXT, key)
        print(f"{cipher[0]} Ciher encrypted text: ", encrypted)
        print(f"{cipher[0]} Ciher decrypted text: ", cipher[2](encrypted, key))


main()