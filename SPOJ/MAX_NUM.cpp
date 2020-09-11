#include<bits/stdc++.h>
using namespace std;

int T, K;
string number;
vector<int> pos[10];

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        for (int i = 0; i < 10; i++)
            pos[i].clear();

        cin >> number >> K;

        int numLeadingZeroes = 0;
        for (int i = 0; i < number.length() && number[i] == '0'; i++)
            numLeadingZeroes += 1;

        number = number.substr(min(numLeadingZeroes, K));
        K -= min(K, numLeadingZeroes);

        if (K > 0) {
            for (int i = number.length() - 1; i >= 0; i--)
                pos[number[i] - '0'].push_back(i);

            string answer = "";
            int lastIndex = -1;
            for (int i = 1; i <= number.length() - K; i++) {
                for (int j = 9; j >= 0; j--) {
                    while (pos[j].size() > 0 && pos[j].back() < lastIndex)
                        pos[j].pop_back();

                    if (pos[j].size() == 0)
                        continue;

                    int leftOver = number.length() - pos[j].back();
                    int need = (number.length() - K) - i + 1;

                    if (leftOver >= need) {
                        answer += (char) (j + '0');
                        lastIndex = pos[j].back();
                        pos[j].pop_back();
                        break;
                    }
                }
            }

            cout << answer << endl;
        } else {
            cout << number << endl;
        }
    }
}
