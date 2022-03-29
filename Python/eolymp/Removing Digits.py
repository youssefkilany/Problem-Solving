# https://www.eolymp.com/en/problems/9037

n = int(input())

n+=1

dp = [1000000]*n
dp[0] = 0
for i in range(1,n):
    dgts = list(map(int, str(i)))
    for dgt in dgts:
        if dgt: dp[i] = min(dp[i], 1 + dp[i - dgt])

print(dp[n-1])
