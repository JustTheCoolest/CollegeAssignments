def func2(f):
    a = 20
    b = 90
    f()

def main():
    a = 5
    b = 7
    func = lambda: print(a, b)
    a = 10
    func2(func)

if __name__ == "__main__":
    main()
