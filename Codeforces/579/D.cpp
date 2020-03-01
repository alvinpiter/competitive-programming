#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int minPrefix[MAXN + 3], maxSuffix[MAXN + 3], answer;
string s, t;

int main() {
    cin >> s >> t;

    int ptrS;

    //minPrefix[i] -> Min index j such that t[1..i] is subsequence of s[1..j]
    ptrS = 0;
    for (int i = 0; i < t.length(); i++) {
        while (s[ptrS] != t[i])
            ptrS += 1;

        minPrefix[i + 1] = ptrS + 1;
        ptrS += 1;
    }

    //maxSuffix[i] -> Max index j such that t[i..] is subsequence of s[j..]
    ptrS = s.length() - 1;
    for (int i = t.length() - 1; i >= 0; i--) {
        while (s[ptrS] != t[i])
            ptrS -= 1;

        maxSuffix[i + 1] = ptrS + 1;
        ptrS -= 1;
    }

    answer = max((int) s.length() - minPrefix[t.length()], maxSuffix[1] - 1);
    for (int i = 1; i < t.length(); i++) {
        answer = max(answer, maxSuffix[i + 1] - minPrefix[i] - 1);
    }

    cout << answer << endl;
}
