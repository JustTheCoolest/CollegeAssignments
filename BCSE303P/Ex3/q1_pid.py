import os

pid = os.fork()

if pid==0:
    print("PID seen from child:", os.getpid())
else:
    