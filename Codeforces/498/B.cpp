#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, a;
    vector<pair<int, int> > problems;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        problems.push_back({a, i});
    }

    sort(problems.begin(), problems.end());
    reverse(problems.begin(), problems.end());

    vector<int> chosenIndices;
    int score = 0;

    for (int i = 0; i < k; i++) {
        chosenIndices.push_back(problems[i].second);
        score += problems[i].first;
    }

    sort(chosenIndices.begin(), chosenIndices.end());

    cout << score << endl;
    for (int i = 0; i < k; i++) {
        int cnt = 0;

        cnt += chosenIndices[i];
        if (i > 0) cnt -= chosenIndices[i - 1];
        if (i == k - 1) cnt += (n - chosenIndices[i]);

        cout << cnt << " ";
    }
    cout << endl;
}
