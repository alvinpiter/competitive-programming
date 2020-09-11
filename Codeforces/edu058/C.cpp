#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define segment pair<pair<int, int>, int >

int t, n, answer[MAXN + 3];
vector<segment> segments;

bool compareRightEnd(segment a, segment b) {
    return a.first.second < b.first.second;
}

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        segments.clear();
        for (int i = 0; i < n; i++) {
            int l, r;
            scanf("%d%d", &l, &r);

            segments.push_back({{l, r}, i});
        }

        sort(segments.begin(), segments.end(), compareRightEnd);

        int cutPosition = -1;
        int minL = segments.back().first.first;

        for (int i = n - 2; i >= 0; i--) {
            if (minL > segments[i].first.second) {
                cutPosition = i;
                break;
            }

            minL = min(minL, segments[i].first.first);
        }

        if (cutPosition == -1) {
            printf("-1\n");
            continue;
        }

        for (int i = 0; i <= cutPosition; i++)
            answer[segments[i].second] = 1;

        for (int i = cutPosition + 1; i < n; i++)
            answer[segments[i].second] = 2;

        for (int i = 0; i < n; i++) {
            printf("%d", answer[i]);

            if (i == n - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
}
