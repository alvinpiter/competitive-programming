#include<bits/stdc++.h>
using namespace std;

int T, N, X, totalBalance, currentBalance, solutionCount;
string s;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> X;
        cin >> s;

        totalBalance = 0;
        for (int i = 0; i < N; i++)
            totalBalance += (s[i] == '1' ? -1 : 1);

        currentBalance = 0;
        solutionCount = 0;

        //Beware of the borders. Avoid double counting.
        for (int i = 0; i < s.length(); i++) {
            if (totalBalance == 0) {
                if (currentBalance == X)
                    solutionCount += 1;
            } else {
                int diff = X - currentBalance;
                if ((totalBalance > 0 && diff >= 0) || (totalBalance < 0 && diff <= 0)) {
                    if (abs(diff)%abs(totalBalance) == 0)
                        solutionCount += 1;
                }
            }

            currentBalance += (s[i] == '1' ? -1 : 1);
        }

        if (totalBalance == 0 && solutionCount > 0)
            cout << -1 << endl;
        else
            cout << solutionCount << endl;
    }
}
