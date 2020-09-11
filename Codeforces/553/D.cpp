#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Sort people by largest (a - b) first. Proof is by exchange argument.
*/

int n;
pair<int, int> people[100003];
LL score;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return (a.first - b.first) > (a.second - b.second);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;

        people[i] = {a, b};
    }

    sort(people + 1, people + n + 1, cmp);

    score = 0;
    for (int i = 1; i <= n; i++) {
        score += (LL) people[i].first * (i - 1);
        score += (LL) people[i].second * (n - i);
    }

    cout << score << endl;
}
