import os
import math

n = 10
print("n:", n)

pid = os.fork()

if pid==0:
    print("Factorial:", math.factorial(n))
elif pid>0:
    a, b = -1, +1
    for i in range(n):
        a, b = b, a+b
    print("Fibonacci: ", b)
else:
    print("Fork failed")
