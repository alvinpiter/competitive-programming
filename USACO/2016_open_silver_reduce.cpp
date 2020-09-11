#include<bits/stdc++.h>
using namespace std;
#define MAXC 40000

/*
Assume we want to reduce the rectangle size by enlarging the value of the left border.
To do this, we only need to consider 3 left most points (since we are allowed to take at most 3).
Apply this to all 3 other edges. We will have at most 12 relevant points to be removed.

Generate the subset of these 12 points that has at most 3 member then calculate the area
excluding the removed points. Take the minimum area.
*/

int N;
vector<pair<int, int> > points, sortedY, sortedX;

int main() {
    freopen("reduce.in", "r", stdin);
    freopen("reduce.out", "w", stdout);

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        points.push_back({x, y});
        sortedX.push_back({x, i});
        sortedY.push_back({y, i});
    }

    sort(sortedX.begin(), sortedX.end());
    sort(sortedY.begin(), sortedY.end());

    vector<int> candidate;
    for (int i = 0; i < 3; i++) {
        candidate.push_back(sortedX[i].second);
        candidate.push_back(sortedY[i].second);
    }

    for (int i = N - 1; i >= N - 3; i--) {
        candidate.push_back(sortedX[i].second);
        candidate.push_back(sortedY[i].second);
    }

    int answer = 2000000000;

    int sz = (int) candidate.size();
    for (int mask = 0; mask < (1 << sz); mask++) {
        set<int> chosen;
        for (int i = 0; i < sz; i++) {
            if (mask & (1 << i))
                chosen.insert(candidate[i]);
        }

        //This part is run at most sum(C(12, i)), for i <= 3
        if (chosen.size() <= 3) {
            int minX = MAXC, maxX = 1, minY = MAXC, maxY = 1;
            for (int i = 0; i < N; i++) {
                if (chosen.find(i) == chosen.end()) {
                    minX = min(minX, points[i].first);
                    maxX = max(maxX, points[i].first);
                    minY = min(minY, points[i].second);
                    maxY = max(maxY, points[i].second);
                }
            }

            answer = min(answer, (maxX - minX)*(maxY - minY));
        }
    }

    printf("%d\n", answer);
}
