# Problem D
Assume at particular bit position, there are count0 0's and count1 1's. In the end there will be count0*count1 1's in this bit position, so it contributes count0*count1*2^i to the answer. Do this for every bit position.

# Problem E
Define dp[i][j][b] as "can we reach cell (i, j) and end up with balance equal b?"
Implementing this dp naively will result in TLE or MLE because it takes O(N^5) time and space. Fortunately we can optimize it significantly with these observations:
* Whenever we are in row i, we only need information about the previous row. Thus we can use flying table technique here and our dp now becomes dp[2][j][b].
* The maximum reachable balance is small, i.e only (80 + 80)*80, or O(N^2).

Up until now, the memory complexity is O(N^3) and time complexity is O(N^4), which is good enough. Be careful because the value of b might be negative.
