#include<bits/stdc++.h>
using namespace std;
#define MAXLG 20

//dp[mask] = maximum length of substring such that it has characters which is subset of mask
int dp[(1 << MAXLG) + 3];
string s;

int main() {
    cin >> s;

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < s.length(); i++) {
        int currentMask = 0;

        //This loop will stop in at most 20 iterations
        for (int j = i; j < s.length(); j++) {
            int charIndex = (s[j] - 'a');
            if (currentMask & (1 << charIndex))
                break;

            currentMask |= (1 << charIndex);
            dp[currentMask] = j - i + 1;
        }
    }

    for (int mask = 0; mask < (1 << MAXLG); mask++) {
        for (int i = 0; i < MAXLG; i++) {
            if (mask & (1 << i))
                dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
        }
    }

    int answer = 0;
    for (int mask = 0; mask < (1 << MAXLG); mask++) {
        answer = max(answer, dp[mask]); //The answer is only from one substring
        answer = max(answer, dp[mask] + dp[((1 << MAXLG) - 1) ^ mask]); //The answer is from two substring
    }

    cout << answer << endl;
}
