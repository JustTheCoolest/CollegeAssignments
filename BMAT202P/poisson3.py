def probability(x, n, func):
    P = 0
    if n == 0:
        return 1;
    for i in range(x, -1, -1):
        P += func(i) * probability(x-i, n-1, func)
    return P

L = 2
probability(3, 3, lambda x: dpois(x, L))