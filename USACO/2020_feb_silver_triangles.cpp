#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000
#define OFFSET 10000

/*
Whenever we use (xi, yi) as the right angle, the total area of triangle will be:
sum(abs(xj - xi)) * sum(abs(yj - yi)), where xj are points whose yj = yi and yj are points
whose xj = xi.

Let's say we want to calculate si = sum(abs(xi - xj)) over x1 <= x2 <= x3 .. <= xn.
We can create recurrence relation:
si+1 = si + (2*i - n)(xi+1 - xi)

Proof hint: kinda like line sweep.
*/

int N;
vector<pair<int, int> > points;
vector<pair<int, int> > todo[2 * OFFSET + 3]; //{coordinate, index}
LL mul[MAXN + 3]; //mul[i] = result of sum(abs(xj - xi)) * sum(abs(yj - yi))

//do the sum thing
void doo() {
    for (int c = 0; c <= 2 * OFFSET; c++) {
        if (todo[c].empty())
            continue;

        sort(todo[c].begin(), todo[c].end());

        int sz = todo[c].size();

        LL s = 0;
        for (int i = 1; i < sz; i++)
            s += todo[c][i].first - todo[c][0].first;

        for (int i = 0; i < sz; i++) {
            if (i > 0)
                s = (s + (2 * i - sz)*(todo[c][i].first - todo[c][i - 1].first))%MOD;

            int idx = todo[c][i].second;
            mul[idx] = (mul[idx] * s)%MOD;
        }
    }
}

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;

        x += OFFSET;
        y += OFFSET;
        points.push_back({x, y});

        mul[i] = 1;
    }

    for (int i = 0; i <= 2 * OFFSET; i++)
        todo[i].clear();

    for (int i = 0; i < N; i++)
        todo[points[i].first].push_back({points[i].second, i});

    doo();

    for (int i = 0; i <= 2 * OFFSET; i++)
        todo[i].clear();

    for (int i = 0; i < N; i++)
        todo[points[i].second].push_back({points[i].first, i});

    doo();

    LL answer = 0;
    for (int i = 0; i < N; i++)
        answer = (answer + mul[i])%MOD;

    cout << answer << endl;
}
