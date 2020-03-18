#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

struct Project {
    int startingDay, endingDay, reward;
    Project() {}
    Project(int _startingDay, int _endingDay, int _reward): startingDay(_startingDay), endingDay(_endingDay), reward(_reward) {};
};

bool compareProjectByStartingDay(Project a, Project b) {
    return a.startingDay < b.startingDay;
}

int N;
Project projects[MAXN + 3];
LL dp[MAXN + 3];

LL solve(int idx) {
    if (idx == N + 1)
        return 0;

    if (dp[idx] != -1)
        return dp[idx];

    LL leave = solve(idx + 1);

    //Find the first job whose starting day is larger than current job ending day
    int lo = idx, hi = N, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (projects[mid].startingDay <= projects[idx].endingDay)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    LL take = solve(lo) + projects[idx].reward;

    return dp[idx] = max(leave, take);
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int a, b, p;
        cin >> a >> b >> p;

        projects[i] = Project(a, b, p);
    }

    sort(projects + 1, projects + N + 1, compareProjectByStartingDay);

    memset(dp, -1, sizeof(dp));

    cout << solve(1) << endl;
}
