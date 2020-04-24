#include<bits/stdc++.h>
using namespace std;
#define INF 1000000
#define MAXN 2000

/*
dp[i][j] -> Is it possible to turn on exactly j bars on digits i to n such that it shows a valid sequence of numbers
*/

int n, k, dp[MAXN + 3][MAXN + 3];
string digits[MAXN + 3];
string binaries[] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

//Number of operations needed to convert binary string a to binary string b.
int calculateCost(string a, string b) {
    int cost = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '0' && b[i] == '1')
            cost += 1;

        if (a[i] == '1' && b[i] == '0')
            return INF;
    }

    return cost;
}

int isPossible(int i, int j) {
    if (i == n + 1)
        return (j == 0 ? 1 : 0);

    if (dp[i][j] != -1)
        return dp[i][j];

    int possible = 0;

    //try changing this digit into num
    for (int num = 0; num <= 9; num++) {
        int cost = calculateCost(digits[i], binaries[num]);
        if (j >= cost)
            possible = max(possible, isPossible(i + 1, j - cost));
    }

    return dp[i][j] = possible;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> digits[i];

    memset(dp, -1, sizeof(dp));

    if (isPossible(1, k) == 0)
        cout << -1 << endl;
    else {
        //try to maximize the digit at each index, starting from the first one.
        for (int i = 1; i <= n; i++) {
            for (int num = 9; num >= 0; num--) {
                int cost = calculateCost(digits[i], binaries[num]);
                if (k >= cost && isPossible(i + 1, k - cost) == 1) {
                    cout << num;

                    k -= cost;
                    break;
                }
            }
        }
        cout << endl;
    }
}
