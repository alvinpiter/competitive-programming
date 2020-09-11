#include<bits/stdc++.h>
using namespace std;

/*
Observation:
Notice that:
* lsb cycles like 01010101
* second lsb cycles like 001100110011
* third lsb cycles like 0000111100001111
* and so on

First we will decide if the missing number is odd or even.
We do this by counting how many numbers has lsb on and off.
If numOff <= numOn, then the missing number is even.
After that, we can half the candidate for the answer, for example if we know the answer is even, we dont have to consider index with odd numbers.

After halving the candidates, we move to the second lsb. Notice that the second lsb of remaining numbers will cycle like 010101.
So we can use previous approach again.

Do it repeatedly for all bit.
*/

int ask(int idx, int bit) {
    cout << "? " << idx << " " << bit << endl;
    cout.flush();

    int response;
    cin >> response;

    return response;
}

int main() {
    int n, answer;
    bool blacklisted[1003];

    cin >> n;

    memset(blacklisted, false, sizeof(blacklisted));
    answer = 0;

    for (int bit = 0; bit <= 10; bit++) {
        bool allBlacklisted = true;
        for (int i = 1; i <= n; i++) {
            if (blacklisted[i] == false)
                allBlacklisted = false;
        }

        if (allBlacklisted)
            break;

        vector<int> oddIndices;
        vector<int> evenIndices;

        for (int i = 1; i <= n; i++) {
            if (blacklisted[i])
                continue;

            int response = ask(i, bit);
            if (response == 0)
                evenIndices.push_back(i);
            else
                oddIndices.push_back(i);
        }

        if ((int) evenIndices.size() <= (int) oddIndices.size()) {
            for (auto o: oddIndices)
                blacklisted[o] = true;
        } else {
            answer += (1 << bit);
            for (auto e: evenIndices)
                blacklisted[e] = true;
        }
    }

    cout << "! " << answer << endl;
    cout.flush();
}
