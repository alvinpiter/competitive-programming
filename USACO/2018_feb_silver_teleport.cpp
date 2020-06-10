#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000000

/*
Define fi(y) as the cost for transporting the i-th stuff if the teleport is targeted at y.
fi(y) = min(abs(ai - bi), abs(a) + abs(y - bi))

If we plot fi(y) we will find that either it is flat all the time or it is flat-go down-go up-flat (kinda like letter V).
With this observation, the solution would be line sweep algorithhm.
It's quite tedious to plot the graph (find out where the 'go down' and 'go-up' begin),
just do case by base analysis.
*/

int N;
map<int, int> delta;
LL currentCost, bestCost;

int main() {
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);

    cin >> N;

    currentCost = 0;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;

        currentCost += abs(a - b);

        //It is better to go straight to b instead of go to 0 then to b
        if (abs(a - b) - abs(a) <= 0)
            continue;

        delta[b] += 2;
        if (a < 0) {
            if (b <= a) {
                delta[2*a] -= 1;
                delta[2*b - 2*a] -= 1;
            } else if (b > 0) {
                delta[0] -= 1;
                delta[2*b] -= 1;
            }
        } else {
            if (b < 0) {
                delta[0] -= 1;
                delta[2*b] -= 1;
            } else if (b >= a) {
                delta[2*a] -= 1;
                delta[2*b - 2*a] -= 1;
            }
        }
    }

    bestCost = currentCost;

    int lastX = -INF;
    int sumDelta = 0;
    for (auto d: delta) {
        currentCost += (LL) sumDelta * (d.first - lastX);

        lastX = d.first;
        sumDelta += d.second;

        bestCost = min(bestCost, currentCost);
    }

    cout << bestCost << endl;
}
