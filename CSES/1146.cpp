#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXLG 60

LL n, dp[MAXLG + 3]; //dp[i] = how many 1 bits between 0 to 111...111 (i bits)

//How many 1 bits between 1 to number - 1. number is given in base 10.
LL count(LL number) {
    vector<int> binary;
    while (number > 0) {
        binary.push_back(number%2);
        number /= 2;
    }

    LL result = 0;
    int numOne = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == 1) {
            result += (1LL << i) * numOne + dp[i];
            numOne += 1;
        }
    }

    return result;
}

int main() {
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= MAXLG; i++)
        dp[i] = dp[i - 1] * 2 + (1LL << (i - 1));

    cin >> n;
    cout << count(n + 1) << endl;
}
