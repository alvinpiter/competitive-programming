#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int q;
LL n, p3[40];
vector<int> base3;

int main() {
    p3[0] = 1;
    for (int i = 1; i < 40; i++)
        p3[i] = 3 * p3[i - 1];

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;

        base3.clear();
        while (n > 0) {
            base3.push_back(n%3);
            n /= 3;
        }

        int leftMost2 = -1;
        for (int i = base3.size() - 1; i >= 0; i--) {
            if (base3[i] == 2) {
                leftMost2 = i;
                break;
            }
        }

        if (leftMost2 != -1) {
            int idxZero = -1;
            for (int i = leftMost2; i < base3.size(); i++) {
                if (base3[i] == 0) {
                    idxZero = i;
                    break;
                }
            }

            if (idxZero == -1) {
                base3.push_back(1);
                for (int i = base3.size() - 2; i >= 0; i--)
                    base3[i] = 0;
            } else {
                base3[idxZero] = 1;
                for (int i = idxZero - 1; i >= 0; i--)
                    base3[i] = 0;
            }
        }

        LL answer = 0;
        for (int i = 0; i < base3.size(); i++)
            answer += base3[i] * p3[i];

        cout << answer << endl;
    }
}
