#include<bits/stdc++.h>
using namespace std;

int N, K, currentPos;
vector<pair<int, int> > events; //{when, in/out}

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);

    cin >> N >> K;

    currentPos = 0;
    for (int i = 1; i <= N; i++) {
        int len;
        string dir;

        cin >> len >> dir;
        if (dir == "R") {
            events.push_back({currentPos, 1});
            events.push_back({currentPos + len, -1});

            currentPos += len;
        } else {
            events.push_back({currentPos, -1});
            events.push_back({currentPos - len, 1});

            currentPos -= len;
        }
    }

    sort(events.begin(), events.end());

    int totalCovered = 0;
    int numCoats = 0;
    int lastPos = 0;
    for (int i = 0; i < 2 * N; ) {
        if (numCoats >= K)
            totalCovered += events[i].first - lastPos;

        lastPos = events[i].first;

        int j;
        for (j = i; j < 2 * N && events[j].first == events[i].first; j++) {
            numCoats += events[j].second;
        }

        i = j;
    }

    cout << totalCovered << endl;
}
