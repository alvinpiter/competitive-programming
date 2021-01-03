#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

/*
Calculate the horizontal cost and vertical cost separately.

Vertical cost is easy, just put all the players on the median of y coordinates.
Horizontal cost is calculated by minimizing this function f(x) = sum(x[i] - (X + i))

Notice that f(x) graph will be U-shaped. Proof:
Assume we start with x = -INF. Each time we will shift x by 1, i.e. goes to x + 1.
f(x) will decrease if number of points that are getting closer is larger than number of points that are getting further.
Once f(x) increase, it will keep increasing because number of points getting further can't decrease.
*/

int T, N;
vector<int> xs, ys;

LL calculateCostY(int y) {
    LL result = 0;
    for (int i = 0; i < ys.size(); i++) {
        result = result + abs(ys[i] - y);
    }

    return result;
}

LL calculateCostX(int x) {
    LL result = 0;
    for (int i = 0; i < xs.size(); i++) {
        result = result + abs(xs[i] - (x + i));
    }

    return result;
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);

        xs.clear();
        ys.clear();
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d%d", &x, &y);

            xs.push_back(x);
            ys.push_back(y);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        int bestY = ys[N/2];
        int bestX;

        int lo = -(MOD + 100000), mid, hi = (MOD + 100000);
        while (hi >= lo) {
            mid = (lo + hi)/2;

            LL prev = calculateCostX(mid - 1);
            LL curr = calculateCostX(mid);
            LL next = calculateCostX(mid + 1);

            if (prev > curr && curr > next) {
                lo = mid + 1;
                continue;
            }

            if (prev < curr && curr < next) {
                hi = mid - 1;
                continue;
            }

            bestX = mid;
            break;
        }


        LL costX = calculateCostX(bestX);
        LL costY = calculateCostY(bestY);

        printf("Case #%d: %lld\n", cases, costY + costX);
    }
}
