#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000
/*
Two numbers a and b will fulfill a + b = a XOR b if every a AND b is 0.
a AND b is 0 means that there is no bit position where both bit a and bit b is 1.

Hence the problem is solvable with digit dp.
*/

LL p2[MAXN + 3], p3[MAXN + 3];

//how many pairs of a and b such that a + b <= s and a AND b is 0
LL f(string s) {
    int n = (int) s.length();

    LL result = 0;
    int cntOneInPrefix = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            continue;
        else {
            result = (result + (p2[cntOneInPrefix] * p3[n - i - 1])%MOD)%MOD;
            cntOneInPrefix += 1;
        }
    }

    return result;
}

int main() {
    p2[0] = p3[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        p2[i] = (p2[i - 1] * 2)%MOD;
        p3[i] = (p3[i - 1] * 3)%MOD;
    }

    string s;
    cin >> s;

    LL answer = f(s);

    int cntOne = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        cntOne += (s[i] == '1');
    }

    answer = (answer + p2[cntOne])%MOD;

    cout << answer << endl;
}
