#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

struct Competition {
    int start, end, score, index;
    Competition(int _start, int _end, int _score, int _index): start(_start), end(_end), score(_score), index(_index) {}
};

bool compareStartTime(Competition a, Competition b) {
    return a.start < b.start;
}

int n, solution[MAXN + 3];
vector<Competition> comps;
pair<LL, LL> dp[MAXN + 3]; // {max score, min duration}

//get competition that start at least at t
int getCompetition(int t) {
    int lo = 0, hi = n - 1, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (comps[mid].start < t)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo;
}

pair<LL, LL> add(pair<LL, LL> p1, pair<LL, LL> p2) {
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

pair<LL, LL> solve(int idx) {
    if (idx == n) {
        return {0, 0};
    }

    if (dp[idx].first != -1)
        return dp[idx];

    pair<LL, LL> leave = solve(idx + 1);
    pair<LL, LL> take = add(make_pair(comps[idx].score, comps[idx].end - comps[idx].start), solve(getCompetition(comps[idx].end)));

    if (leave.first == take.first) {
        if (leave.second < take.second) {
            solution[idx] = 0;
            return dp[idx] = leave;
        } else {
            solution[idx] = 1;
            return dp[idx] = take;
        }
    } else if (leave.first > take.first) {
        solution[idx] = 0;
        return dp[idx] = leave;
    } else if (leave.first < take.first) {
        solution[idx] = 1;
        return dp[idx] = take;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        comps.push_back(Competition(a, b, c, i));
    }

    sort(comps.begin(), comps.end(), compareStartTime);

    for (int i = 0; i < n; i++) {
        dp[i] = {-1, -1};
        solution[i] = -1;
    }

    auto best = solve(0);

    vector<int> indices;
    int current = 0;
    while (current != n) {
        if (solution[current] == 1) {
            indices.push_back(comps[current].index + 1);
            current = getCompetition(comps[current].end);
        } else {
            current = current + 1;
        }
    }

    sort(indices.begin(), indices.end());

    printf("%d %lld %lld\n", (int) indices.size(), best.first, best.second);
    for (auto idx: indices)
        cout << idx << " ";
    cout << endl;
}

/*
5
1 6 7
2 3 2
3 8 6
7 10 3
8 9 3

5
1 6 7
2 3 2
3 8 5
7 10 3
8 9 3
*/
