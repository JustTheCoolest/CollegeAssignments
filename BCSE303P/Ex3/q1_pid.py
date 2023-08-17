import os

pid = os.fork()

if pid==0:
    print("PID seen from child:", os.getpid())
elif pid>0:
    print("PID of parent:", os.getpid())
    print("PID of child seen from parent:", pid)
else:
    print("Fork failed")
