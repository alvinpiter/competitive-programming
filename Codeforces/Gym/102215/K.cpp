#include<bits/stdc++.h>
using namespace std;

/*
If number of unique characters is < 3, the answer is YES. Otherwise:

Define the final ordering (we can bruteforce it), let's say it's RGB.
Now we will check if we can construct RGB using the string. Algorithm:
* Take all R and put it into first pile
* Take as many G's as possible (after the last R)
* The remaining string must be some G's (possibly 0) followed by some B's
*/

int main() {
    string s;
    bool taken[1003], possible;
    char chars[] = {'R', 'G', 'B'};

    cin >> s;

    int n = (int) s.length();

    set<char> uniq;
    for (int i = 0; i < n; i++) {
        uniq.insert(s[i]);
    }

    if ((int) uniq.size() < 3) {
        cout << "YES\n";
        return 0;
    }

    possible = false;
    for (int first = 0; first < 3; first++) {
        for (int second = 0; second < 3; second++) {
            for (int third = 0; third < 3; third++) {
                if (first == second || first == third || second == third)
                    continue;

                memset(taken, false, sizeof(taken));

                int lastIndexOfFirstCharacter = -1;
                for (int i = 0; i < n; i++) {
                    if (s[i] == chars[first]) {
                        taken[i] = true;
                        lastIndexOfFirstCharacter = i;
                    }
                }

                for (int i = lastIndexOfFirstCharacter + 1; i < n; i++) {
                    if (s[i] == chars[second]) {
                        taken[i] = true;
                    }
                }

                int firstIndexOfThirdCharacter = -1;
                for (int i = 0; i < n; i++) {
                    if (s[i] == chars[third]) {
                        firstIndexOfThirdCharacter = i;
                        break;
                    }
                }

                bool can = true;
                for (int i = firstIndexOfThirdCharacter + 1; i < n; i++) {
                    if (s[i] == chars[second] && !taken[i]) {
                        can = false;
                        break;
                    }
                }

                if (can)
                    possible = true;
            }
        }
    }

    if (possible)
        cout << "YES\n";
    else
        cout << "NO\n";
}
