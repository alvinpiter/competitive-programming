#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int t, n, m;

string toBinary(LL num) {
    string result = "";

    while (num > 0) {
        result = (char) (num%2 + '0') + result;
        num /= 2;
    }

    while ((int) result.length() < m)
        result = '0' + result;

    return result;
}

LL toInteger(string binary) {
    LL result = 0;
    for (int i = 0; i < m; i++) {
        if (binary[i] == '1')
            result += (1LL << (m - i - 1));
    }

    return result;
}

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;

        vector<LL> removed;

        removed.push_back(-1);//dummy
        removed.push_back(1LL << m);//dummy

        for (int i = 0; i < n; i++) {
            string binary;
            cin >> binary;

            removed.push_back(toInteger(binary));
        }

        sort(removed.begin(), removed.end());

        LL cnt = 0;
        LL target = ((1LL << m) - n - 1)/2 + 1;

        for (int i = 1; i < (int) removed.size(); i++) {
            LL currCnt = removed[i] - removed[i - 1] - 1;

            if (cnt + currCnt >= target) {
                LL ans = removed[i - 1] + (target - cnt);
                cout << toBinary(ans) << endl;
                break;
            } else
                cnt += currCnt;
        }
    }
}
