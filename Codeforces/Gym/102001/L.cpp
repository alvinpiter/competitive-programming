#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL toDecimal(string s) {
    LL result = 0;
    LL multiplier = 1;
    for (int i = s.length() - 1; i >= 0; i--) {
        result += multiplier * (s[i] - '0');
        multiplier *= 2;
    }

    return result;
}

string toBinary(LL num) {
    string result = "";
    while (num > 0) {
        result = (char) (num%2 + '0') + result;
        num /= 2;
    }

    return result;
}

int main() {
    LL K;
    string S;
    int answer;

    cin >> K;
    cin >> S;

    answer = 100;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == '0')
            continue;

        int cost = i;
        string temp = S.substr(i);

        while (toDecimal(temp) > K) {
            int idxOne = -1;
            for (int i = 1; i < temp.length(); i++) {
                if (temp[i] == '1') {
                    idxOne = i;
                    break;
                }
            }

            cost += 1;
            if (idxOne == -1) {
                temp = temp[0] + temp.substr(2);
            } else {
                temp = temp.substr(0, idxOne) + temp.substr(idxOne + 1);
            }
        }

        answer = min(answer, cost);
    }

    cout << answer << endl;
}
