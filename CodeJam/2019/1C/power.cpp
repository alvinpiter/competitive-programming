#include<bits/stdc++.h>
using namespace std;

string ask(int position) {
    cout << position << endl;
    cout << flush;

    string response;
    cin >> response;

    return response;
}

string answer(string ans) {
    cout << ans << endl;
    cout << flush;

    string response;
    cin >> response;

    return response;
}

int main() {
    const int numChar = 5;
    const int numGroup = 119;
    int T, F, counter[numChar];
    int fact[] = {1, 1, 2, 6, 24};
    char groupChar[numGroup + 3][numChar]; //groupChar[i][j] -> j-th character of i-th group

    //blacklisted[i] -> true if this group is not relevant anymore (the prefix doesn't match the answer)
    //done[i] -> whether we have used character i in answer
    bool blacklisted[numGroup + 3], done[numChar];
    string ans;

    cin >> T >> F;
    for (int cases = 1; cases <= T; cases++) {
        memset(blacklisted, false, sizeof(blacklisted));
        memset(done, false, sizeof(done));
        ans = "";

        //we want to find out the i-th character in our missing permutation
        for (int i = 0; i < numChar - 1; i++) {
            memset(counter, 0, sizeof(counter));

            for (int j = 0; j < numGroup; j++) {
                if (!blacklisted[j]) {
                    string response = ask(j * numChar + i + 1);

                    counter[response[0] - 'A'] += 1;
                    groupChar[j][i] = response[0];
                }
            }

            //if the counter is fact[numChar - i - 1] - 1, then that is our missing character
            for (int c = 0; c < numChar; c++) {
                if (counter[c] == fact[numChar - i - 1] - 1 && done[c] == false) {
                    ans += (char) (c + 'A');
                    done[c] = true;
                    break;
                }
            }

            //blacklist some group
            for (int j = 0; j < numGroup; j++) {
                if (groupChar[j][i] != ans[i])
                    blacklisted[j] = true;
            }
        }

        for (int c = 0; c < numChar; c++) {
            if (!done[c])
                ans += (char) (c + 'A');
        }

        string response = answer(ans);
        if (response == "Y")
            continue;
        else
            break;
    }
}
