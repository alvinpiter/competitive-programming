#include<bits/stdc++.h>
using namespace std;

string S, P;
int counterS[26], counterP[26];

int main() {
    cin >> S >> P;

    memset(counterS, 0, sizeof(counterS));
    memset(counterP, 0, sizeof(counterP));

    for (int i = 0; i < S.length(); i++)
        counterS[S[i] - 'a'] += 1;

    for (int i = 0; i < P.length(); i++)
        counterP[P[i] - 'a'] += 1;

    bool valid = true;
    for (int i = 0; i < 26; i++) {
        if (counterP[i] > counterS[i])
            valid = false;
    }

    if (valid)
        cout << "YES\n";
    else
        cout << "NO\n";
}
