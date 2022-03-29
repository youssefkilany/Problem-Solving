# https://www.eolymp.com/en/problems/1560

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
    while True:
        try:
            n = int(input())
        except Exception:
            break
        
        if n == 1:
            print(0); continue
        if n == 2 or n == 3:
            print(1); continue
        
        dp = [1e6]*(n+1)
        dp[2] = dp[3] = 1
        
        for i in range(4, n+1):
            res = dp[i-1]
            if i % 2 == 0:
                res = min(res, dp[i//2])
            if i % 3 == 0:
                res = min(res, dp[i//3])
            dp[i] = 1 + res
        
        print(dp[n])

def main():
    T = 1
#     T = inp()
    for _ in range(T):
        solve()

if __name__ == "__main__":
    main()
