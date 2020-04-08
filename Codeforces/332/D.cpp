#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL X;
    vector<pair<LL, LL> > answer;

    cin >> X;
    for (LL n = 1; n <= 1450000; n++) {
        LL numerator = 6*X - n*(n - 1)*(2*n - 1) + 3*n*n*(n - 1);
        LL denominator = 6*n*n - 3*n*(n - 1);

        if (abs(numerator)%abs(denominator) == 0) {
            LL m = numerator/denominator;

            if (m > 0 && n <= m)
                answer.push_back({n, m});
        }
    }

    int sz = answer.size();
    for (int i = 0; i < sz; i++) {
        if (answer[i].first != answer[i].second) {
            answer.push_back({answer[i].second, answer[i].first});
        }
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << endl;
    for (auto a: answer) {
        cout << a.first << " " << a.second << endl;
    }
}
