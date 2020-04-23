#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define B1 41
#define B2 73
#define M1 998244353
#define M2 1000000007
#define MAXN 1000000

/*
Algorithm:
* Find index i and j such that s[1..i] = s[j..n].
* Find longest palindromic prefix/suffix in substring (i + 1..j - 1).
*/

LL b1[MAXN + 3], b2[MAXN + 3];

string longestPalindromicPrefix(string s) {
    string revS = s;
    reverse(revS.begin(), revS.end());

    int best = 0;
    pair<LL, LL> prefixHash = {0, 0};
    pair<LL, LL> suffixHash = {0, 0};

    int len = s.length();
    int l = 0, r = len - 1;
    for (int rep = 1; rep <= s.length(); rep++) {
        int prefixChar = (s[l] - 'a') + 1;
        prefixHash.first = (prefixHash.first + b1[l] * prefixChar)%M1;
        prefixHash.second = (prefixHash.second + b2[l] * prefixChar)%M2;

        int suffixChar = (revS[r] - 'a') + 1;
        suffixHash.first = (suffixHash.first * B1)%M1;
        suffixHash.first = (suffixHash.first + suffixChar)%M1;

        suffixHash.second = (suffixHash.second * B2)%M2;
        suffixHash.second = (suffixHash.second + suffixChar)%M2;

        if (prefixHash == suffixHash)
            best = l + 1;

        l += 1;
        r -= 1;
    }

    return s.substr(0, best);
}

int main() {
    b1[0] = 1;
    b2[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        b1[i] = (b1[i - 1] * B1)%M1;
        b2[i] = (b2[i - 1] * B2)%M2;
    }

    int t;
    string s, answer1, answer2;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        cin >> s;

        int l = 0, r = s.length() - 1;
        while (l < r && s[l] == s[r]) {
            l += 1;
            r -= 1;
        }

        if (l == r) {
            cout << s << endl;
        } else {
            string prefix = s.substr(0, l);
            string suffix = s.substr(r + 1);
            string middle = s.substr(l, r - l + 1);

            answer1 = prefix + longestPalindromicPrefix(middle) + suffix;

            reverse(middle.begin(), middle.end());
            answer2 = prefix + longestPalindromicPrefix(middle) + suffix;

            if (answer1.length() > answer2.length())
                cout << answer1 << endl;
            else
                cout << answer2 << endl;
        }
    }
}
