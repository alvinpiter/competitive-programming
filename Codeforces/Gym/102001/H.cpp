#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100000

/*
Convert each constraint to be "How many -1 can this segment has?"
Maintain active segments in some container. At each point, we want to know the segment which can take the least number of -1.
If the count is < 0, then Impossible
If the count is = 0, then current value must be 1
If the count is > 0, then current value must be -1

Whenever we process a segment, we would like to know how many -1 it already took. To do this, we can use a simple trick:
Instead of pushing the actual number of -1 it can take, push the actual number of -1 it can take + number of -1 so far.

Then the number of -1 a segment can take now is value - (number of -1 so far).
*/

int N, K, p[MAXN + 3], psum[MAXN + 3];
pair<pair<int, int>, int> cons[MAXN + 3];
vector<pair<int, int> > events[MAXN + 3]; //only record opening events. {maxNegative, right end}

int main() {
    scanf("%d%d", &N, &K);

    memset(psum, 0, sizeof(psum));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &p[i]);
        if (p[i] == -1)
            psum[i] = 1;
    }

    for (int i = 2; i <= N; i++)
        psum[i] += psum[i - 1];

    for (int i = 1; i <= K; i++) {
        scanf("%d%d%d", &cons[i].first.first, &cons[i].first.second, &cons[i].second);
        int maxNegative = ((cons[i].first.second - cons[i].first.first + 1) - cons[i].second)/2;
        maxNegative -= psum[cons[i].first.second] - psum[cons[i].first.first - 1];

        events[cons[i].first.first].push_back({maxNegative, cons[i].first.second});
    }

    priority_queue<pair<int, int> > pq; //{negative, right end}

    int cntNegative = 0;
    for (int i = 1; i <= N; i++) {
        //remove out of range segments
        while (!pq.empty() && pq.top().second < i)
            pq.pop();

        for (auto event: events[i])
            pq.push({-(event.first + cntNegative), event.second});

        if (p[i] != 0) continue;

        int quota = (pq.empty() ? INF : -pq.top().first);
        quota -= cntNegative;

        if (quota < 0) {
            printf("Impossible\n");
            return 0;
        } else if (quota == 0) {
            p[i] = 1;
        } else {
            p[i] = -1;
            cntNegative += 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (i > 1) printf(" ");
        printf("%d", p[i]);
    }
    printf("\n");
}
