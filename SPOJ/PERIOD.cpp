#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int T, N, F[MAXN + 3];
string text;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;
        cin >> text;

        //Calculate failure function
        F[0] = -1;
        int prevF = F[0];
        for (int i = 1; i <= N; i++) {
            while (prevF != -1 && text[i - 1] != text[prevF])
                prevF = F[prevF];

            F[i] = prevF + 1;
            prevF = F[i];
        }

        //Blank line after each test case
        if (cases > 1)
            cout << endl;

        cout << "Test case #" << cases << endl;
        for (int i = 0; i < N; i++) {
            //Doesn't overlap
            if (2 * F[i + 1] < i + 1)
                continue;

            int segmentLength = (i + 1) - F[i + 1];
            if ((i + 1)%segmentLength == 0)
                cout << i + 1 << " " << (i + 1)/segmentLength << endl;
        }
    }
}
