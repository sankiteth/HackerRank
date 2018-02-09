#!/bin/python3

import sys

def fibonacciModified(t1, t2, n):
    dp = [0, t1, t2]
    for i in range(3, n+1):
        dp.append(dp[i-2] +  dp[i-1]**2)
    
    return dp[n]

if __name__ == "__main__":
    t1, t2, n = input().strip().split(' ')
    t1, t2, n = [int(t1), int(t2), int(n)]
    result = fibonacciModified(t1, t2, n)
    print(result)