# https://www.eolymp.com/en/problems/798

from io import BytesIO, IOBase
import os
import sys

BUFSIZE = 8192

class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = 'x' in file.mode or 'r' not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b: break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b'\n') + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")

try: sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
except: pass

def input(): return sys.stdin.readline().rstrip("\r\n")
def li(): return list(map(int, sys.stdin.readline().split()))
def mp(): return map(int, sys.stdin.readline().split())
def inp(): return int(sys.stdin.readline())
def prl(n): return sys.stdout.write(str(n)+'\n')
def pr(n): return sys.stdout.write(str(n)+' ')

def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    dp = [0] * n
    parent = [-1] * n
    
    dp[1] = abs(A[1] - A[0])
    parent[1] = 0
    
    
    for i in range(2, n):
        a = abs(A[i]-A[i-1])+dp[i-1]
        b = 3*abs(A[i]-A[i-2])+dp[i-2]
        
        if a < b:
            dp[i] = a
            parent[i] = i-1
        else:
            dp[i] = b
            parent[i] = i-2
    
    print(dp[n-1])
    steps = [n-1,]
    while steps[-1] != -1:
        steps.append(parent[steps[-1]])
    steps = steps[:-1]

    print(len(steps))
    print(' '.join(map(lambda x:str(x+1), steps[::-1])))
    
def main():
    T = 1
#     T = inp()
    for _ in range(T):
        solve()

if __name__ == "__main__":
    main()
