#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int suff[200003];
    int cnt[2020];

    memset(suff, 0, sizeof(suff));
    memset(cnt, 0, sizeof(cnt));

    int n = (int) s.length();
    suff[n + 1] = 0;
    cnt[0] = 1;

    long long int answer = 0;

    int mul = 1;
    for (int i = n; i >= 1; i--) {
        int currentDigit = s[i - 1] - '0';
        suff[i] = (mul * currentDigit + suff[i + 1])%2019;

        answer += cnt[suff[i]];
        cnt[suff[i]] += 1;

        mul = (mul * 10)%2019;
    }

    cout << answer << endl;
}
