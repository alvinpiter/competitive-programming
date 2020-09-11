#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

/*
Algorithm:
* Compute lcp[i] -> longest commong prefix between i-th string and (i - 1)-th string.
* Process from the last string. If previous string is larger, cut it.
*/

int n, lcp[MAXN + 3], len[MAXN + 3];
string strings[MAXN + 3];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
        len[i] = (int) strings[i].length();
    }

    for (int i = 1; i < n; i++) {
        lcp[i] = min(len[i], len[i - 1]);
        for (int j = 0; j < min(len[i], len[i - 1]); j++) {
            if (strings[i][j] != strings[i - 1][j]) {
                lcp[i] = j;
                break;
            }
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        int idxToCompare = min(lcp[i], len[i]);

        if (idxToCompare == len[i - 1])
            continue;

        if (idxToCompare == len[i] || strings[i - 1][idxToCompare] > strings[i][idxToCompare])
            len[i - 1] = idxToCompare;
    }

    for (int i = 0; i < n; i++)
        cout << strings[i].substr(0, len[i]) << endl;
}
