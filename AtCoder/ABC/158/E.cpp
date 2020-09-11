#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int N, P;
string S;
LL answer;

int main() {
    cin >> N >> P >> S;

    answer = 0;
    if (P == 2) {
        for (int i = 0; i < N; i++) {
            int digit = S[i] - '0';
            if (digit%2 == 0)
                answer += (i + 1);
        }
    } else if (P == 5) {
        for (int i = 0; i < N; i++) {
            int digit = S[i] - '0';
            if (digit%5 == 0)
                answer += (i + 1);
        }
    } else {
        map<int, int> cnt;

        cnt[0] = 1;
        int suffix = 0;
        int multiplier = 1;
        for (int i = N - 1; i >= 0; i--) {
            int digit = S[i] - '0';

            suffix = ((digit * multiplier) + suffix)%P;

            answer += cnt[suffix];

            cnt[suffix] = cnt[suffix] + 1;
            multiplier = (multiplier * 10)%P;
        }
    }

    cout << answer << endl;
}
