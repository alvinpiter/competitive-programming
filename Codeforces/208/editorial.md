# Problem D
Define dp0[i] -> Maximum score from the first i element given the element next to i has not been taken
Defien dp1[i] -> Maximum score from the first i element given the element next to i has been taken

Notice that in calculating dp0[i] and dp1[i], we dont care how the order of the first i - 2 elements. We only care the order of (i - 1)-th element and i-th element. Formula:
dp0[i] = max(a[i] + dp1[i - 1], b[i] + dp0[i - 1])
dp1[i] = max(b[i] + dp1[i - 1], c[i] + dp0[i - 1])
