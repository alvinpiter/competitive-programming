#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Observation:
Any string that contains at least 2 A's or at least 2 B's are good because for every index i, we can form a palindrome from substring i..j where j is the smallest index such that s[j] = s[i].

Observation:
There are only 6 types of substring that is bad:
* A followed by 1 or more B's (ABBBB..)
* B followed by 1 or more A's (BAAAA..)
* 1 or more B's followed by A (BBBBA..)
* 1 or more A's followed by B (AAAAB..)
* A
* B
*/

int n;
LL cntBad, cntAll;
string s;

int main() {
    cin >> n >> s;

    cntAll = ((LL) n * n + n)/2;
    cntBad = 0;

    int cons;

    cons = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            cntBad += cons;
            cons = 1;
        } else
            cons += 1;
    }

    cons = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] != s[i + 1]) {
            cntBad += cons - 1; //avoid double counting AB
            cons = 1;
        } else
            cons += 1;
    }

    cntBad += n; // just A or just B

    cout << cntAll - cntBad << endl;
}
