#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n, k, nxt[MAXN + 3], prv[MAXN + 3], assignment[MAXN + 3];
    vector<pair<int, int> > students;
    bool taken[MAXN + 3];

    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        students.push_back({a, i});
        prv[i] = i - 1;
        nxt[i] = i + 1;
        taken[i] = false;
    }

    //student with highest programming skill will be at back
    sort(students.begin(), students.end());

    for (int turn = 0; ; turn = (turn + 1)%2) {
        while (!students.empty() && taken[students.back().second] == true)
            students.pop_back();

        if (students.empty())
            break;

        int idx = students.back().second;
        taken[idx] = true;
        assignment[idx] = turn + 1;

        int r = nxt[idx];
        for (int rep = 1; rep <= k; rep++) {
            if (r == n + 1)
                break;

            taken[r] = true;
            assignment[r] = turn + 1;

            r = nxt[r];
        }

        int l = prv[idx];
        for (int rep = 1; rep <= k; rep++) {
            if (l == 0)
                break;

            taken[l] = true;
            assignment[l] = turn + 1;

            l = prv[l];
        }

        nxt[l] = r;
        prv[r] = l;
    }

    for (int i = 1; i <= n; i++)
        printf("%d", assignment[i]);

    printf("\n");
}
