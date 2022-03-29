# https://www.eolymp.com/en/problems/1619

n = int(input())
A = list(map(int, input().split()))

dp = [0]*3
dp[0] = A[0]

if n < 2:
    print(dp[n-1])
    exit(0)

dp[1] = max(A[0], A[1])

if n < 3:
    print(dp[n-1])
    exit(0)

for i in range(2,n):
    dp[i%3] = max(dp[(i-1)%3], dp[(i-2)%3]+A[i])
    
print(dp[(n-1)%3])
