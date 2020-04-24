#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 2e9
#define MAXM 10000
#define MAXG 1000

/*
Model the problem as a graph. Each vertex in the graph will have two values, current point and time left before next red light.
Observe that we can calculate the total time needed to reach the destination just by counting how many red lights we go through.
Assume we go through cnt red lights, then the total time is cnt * (R + G) + (G - g), where g is the "time left before next red light" in destination point.

So we can model the graph as follow:
* If we still have time before next red light, we try to visit the neighbors (if possible). The cost for this action is 0, because we dont go through a red light.
* If we don't have time before next red light, then we will wait at current point. The cost for this action is 1.

To count the number of red light we go through, perform 0-1 BFS.
*/

int N, M, D[MAXM + 3], G, R, dist[MAXM + 3][MAXG + 3];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++)
        scanf("%d", &D[i]);

    scanf("%d%d", &G, &R);

    sort(D + 1, D + M + 1);

    for (int i = 1; i <= M; i++) {
        for (int g = 0; g <= G; g++) {
            dist[i][g] = INF;
        }
    }

    deque<pair<int, int> > dq;

    dist[1][G] = 0;
    dq.push_back({1, G});

    while (!dq.empty()) {
        auto front = dq.front(); dq.pop_front();

        int currentPoint = front.first;
        int timeLeft = front.second;

        if (timeLeft == 0) {
            if (dist[currentPoint][G] == INF) {
                dist[currentPoint][G] = dist[currentPoint][timeLeft] + 1;
                dq.push_back({currentPoint, G});
            }
        } else {
            for (int delta = -1; delta <= 1; delta += 2) {
                int nextPoint = currentPoint + delta;
                int diff = abs(D[currentPoint] - D[nextPoint]);

                if (nextPoint >= 1 && nextPoint <= M && timeLeft >= diff && dist[nextPoint][timeLeft - diff] == INF) {
                    dist[nextPoint][timeLeft - diff] = dist[currentPoint][timeLeft];
                    dq.push_front({nextPoint, timeLeft - diff});
                }
            }
        }
    }

    int ans = INF;
    for (int g = 0; g <= G; g++) {
        if (dist[M][g] < INF) {
            ans = min(ans, dist[M][g] * (R + G) + (G - g));
        }
    }

    if (ans < INF)
        printf("%d\n", ans);
    else
        printf("-1\n");
}
