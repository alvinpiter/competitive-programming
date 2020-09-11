#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100000
#define MAXK 100
#define DEBUG true

/*
Observations:
* Removing too many segments is okay, since we can add them back without changing the answer
* Removing enclosed segment is better, since it doesn't decrease answer.
* After removing enclosed segment, we can sort the segment with left end. The right end will also be sorted.

We can use dynamic programming:
dp[i][rem][removable] -> maximum covered segment using segment i..N when we have to remove at least
rem segments and whether current segment is removable or not.

There are 2 possible transitions:
* We take current segment to answer. The next segment we take is either intersecting with this one or not.
  If it intersects, then it's better to choose the rightmost one.
* We skip current segment

intersect[i] -> largest j such that segments[j].left <= segments[i].right
*/

int N, K, intersect[MAXN + 3], dp[MAXN + 3][MAXK + 3][2];
vector<pair<int, int> > tempSegments, segments;

//Filter out enclosed segments
void filterSegments() {
    sort(tempSegments.begin(), tempSegments.end());

    segments.push_back(tempSegments[0]);

    int maxR = tempSegments[0].second;
    for (int i = 1; i < tempSegments.size(); i++) {
        if (tempSegments[i].second < maxR)
            continue;

        segments.push_back(tempSegments[i]);
        maxR = tempSegments[i].second;
    }
}

void initializeIntersect() {
    for (int i = 0; i < N; i++) {
        int lo = i, hi = N - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (segments[mid].first < segments[i].second)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        intersect[i] = hi;
    }
}

int solve(int i, int rem, int removable) {
    if (i == N)
        return (rem == 0 ? 0 : -INF);

    if (dp[i][rem][removable] != -1)
        return dp[i][rem][removable];

    int best = -INF;
    int j = intersect[i];
    int currSegmentLength = segments[i].second - segments[i].first;

    //option 1, take the last intersecting segment (if possible)
    if (j > i) {
        best = max(best, currSegmentLength + (solve(j, max(0, rem - (j - i - 1)), 0) - (segments[i].second - segments[j].first)));
    }

    //option 2, don't take last intersecting segment
    best = max(best, currSegmentLength + solve(j + 1, max(0, rem - (j - i)), 1));

    //option 3, skip this segment
    if (removable == 1)
        best = max(best, solve(i + 1, max(0, rem - 1), 1));

    return dp[i][rem][removable] = best;
}

int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        int l, r;
        cin >> l >> r;
        tempSegments.push_back({l, r});
    }

    filterSegments();

    //Adjust K and N
    K -= (tempSegments.size() - segments.size());
    K = max(K, 0);

    N = segments.size();

    initializeIntersect();

    memset(dp, -1, sizeof(dp));

    cout << solve(0, K, 1) << endl;
}
