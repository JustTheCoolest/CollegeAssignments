NUM_SIZE = 4 #bytes
NUM_ROUNDS = 64

def sha(message, NUM_SIZE, NUM_ROUNDS):
    message += chr(0x80)
    num_blocks = math.ceil(len(message)+8)\
    mod_base = 2**(NUM_SIZE * 16)
    for x in range(num_blocks):

        block_base = x * 16 * NUM_SIZE
        block = []
        for y in range(16):
            chunk_base = block_base + y * NUM_SIZE
            num = 0
            for z in range(NUM_SIZE):
                curr_index = chunk_base + z
                curr = message[curr_index] if curr_index < len(message) else 0
                num *= NUM_SIZE * 8
                num += curr
                assert curr < 2**8
            block.append(num)
        blocks.append(block)
        # Flag: Using a multi-pass solution at the expense of higher memory complexity, for code simplicity

    size = (len(message) - 1) * 8
    blocks[-1][-2] = size % mod_base # Flag: Ignoring Python's lack of compile phase optimisations
    blocks[-1][-1] = size // mod_base
    assert block[-1][-2] < mod_base

    for block in blocks:
        words = list(block)
        for x in range(16, NUM_ROUNDS):
            word = (sig1(words[x-2]) + words[x-7] + sig0(words[x-15]) + words[x-16]) % mod_base
            words.append(word)
        
        a, b, c, d, e, f, g = H
        for x in range(NUM_ROUNDS):
            T1 = h + bigsig(e) + ch(e, f, g) + K[x] + W[x]
            T2 = bigsig0(a) + maj(a, b, c)
            a, b, c, d, e, f, g, h = (T1+T2)%mod_base, a, b, c, (d+T1)%mod_base, e, f, g

        X
        for x, y in zip(H, (a, b, c, d, e, f, g, h)):
            X.append((x+y)%mod_base)
        H = X

    result = ""
    for comp in H:
        result += to_hex(comp, NUM_SIZE)

    return result


