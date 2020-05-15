#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n;
    pair<int, int> segments[MAXN + 3];
    vector<int> answer;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }

    sort(segments, segments + n);

    int minR = segments[0].second;
    for (int i = 1; i < n; i++) {
        if (segments[i].first > minR) {
            answer.push_back(minR);
            minR = segments[i].second;
        } else {
            minR = min(minR, segments[i].second);
        }
    }

    answer.push_back(minR);

    cout << (int) answer.size() << endl;
    for (int a: answer)
        cout << a << " ";
    cout << endl;
}
