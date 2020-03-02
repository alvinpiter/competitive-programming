#include<bits/stdc++.h>
using namespace std;
#define MAXN 100
#define MAXR 61000

vector<pair<int, int> > posProjects, negProjects;

int N, R, takenPositiveProject;
int dp[MAXN + 3][MAXR + 3]; //dp[i][j] -> Maximum number of negative project from index i to end that can be taken when currently we have j rating.

//Can be proven with exchange argument
bool negProjectComparator(pair<int, int> p1, pair<int, int> p2) {
    return (p1.first + p1.second > p2.first + p2.second);
}

bool posProjectComparator(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first != p2.first)
        return p1.first < p2.first;
    else
        return p1.second > p2.second;
}

int solve(int idx, int rating) {
    if (idx == negProjects.size())
        return 0;

    if (dp[idx][rating] != -1)
        return dp[idx][rating];

    //Leave current project
    int leave = solve(idx + 1, rating);

    //Take current project (if possible)
    int take = 0;
    if (rating >= negProjects[idx].first && rating + negProjects[idx].second >= 0)
        take = 1 + solve(idx + 1, rating + negProjects[idx].second);

    return dp[idx][rating] = max(leave, take);
}

int main() {
    cin >> N >> R;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;

        if (b < 0)
            negProjects.push_back({a, b});
        else
            posProjects.push_back({a, b});
    }

    sort(negProjects.begin(), negProjects.end(), negProjectComparator);
    sort(posProjects.begin(), posProjects.end(), posProjectComparator);

    //Take positive project as many as possible
    takenPositiveProject = 0;
    for (int i = 0; i < posProjects.size(); i++) {
        if (R >= posProjects[i].first) {
            takenPositiveProject += 1;
            R += posProjects[i].second;
        } else
            break;
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, R) + takenPositiveProject << endl;
}
