#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
prefixAB[i] = number of j such that j <= i and A[j] != B[j]
*/

string A, B, C;
int n, prefixAB[MAXN + 3], suffixAB[MAXN + 3], prefixAC[MAXN + 3], suffixAC[MAXN + 3];

int main() {
    cin >> A >> B >> C;

    n = A.length();
    for (int i = 0; i < n; i++) {
        prefixAB[i] = (A[i] != B[i]) + (i == 0 ? 0 : prefixAB[i - 1]);
        prefixAC[i] = (A[i] != C[i]) + (i == 0 ? 0 : prefixAC[i - 1]);
    }

    for (int i = n - 1; i >= 0; i--) {
        suffixAB[i] = (A[i] != B[i]) + (i == n - 1 ? 0 : suffixAB[i + 1]);
        suffixAC[i] = (A[i] != C[i]) + (i == n - 1 ? 0 : suffixAC[i + 1]);
    }

    vector<string> possibilities;

    //no mistake
    if (prefixAB[n - 1] <= 1 && prefixAC[n - 1] <= 1)
        possibilities.push_back(A);

    for (int i = 0; i < n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == A[i])
                continue;

            int diffAB = 0, diffAC = 0;

            diffAB += (i > 0 ? prefixAB[i - 1] : 0);
            diffAB += (i < n - 1 ? suffixAB[i + 1] : 0);
            diffAB += (B[i] != c ? 1 : 0);

            diffAC += (i > 0 ? prefixAC[i - 1] : 0);
            diffAC += (i < n - 1 ? suffixAC[i + 1] : 0);
            diffAC += (C[i] != c ? 1 : 0);

            if (diffAB <= 1 && diffAC <= 1) {
                possibilities.push_back(A.substr(0, i) + c + A.substr(i + 1));
                if ((int) possibilities.size() > 1)
                    break;
            }
        }

        if ((int) possibilities.size() > 1)
            break;
    }

    if (possibilities.empty())
        cout << "Impossible\n";
    else if ((int) possibilities.size() == 1)
        cout << possibilities[0] << endl;
    else
        cout << "Ambiguous\n";
}
