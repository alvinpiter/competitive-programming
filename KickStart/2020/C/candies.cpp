#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

/*
Example: A = [1, 2, 3, 4, 5]. Picture it as a stair:
          5
       -4 5
     3 -4 5
  -2 3 -4 5
1 -2 3 -4 5

The answer to a query is a sum of numbers in a triangle.
*/

class BIT {
private:
    int N;
    LL bit[MAXN + 3];

public:
    BIT(int _N) {
        N = _N;
        memset(bit, 0, sizeof(bit));
    }

    void update(int idx, int val) {
        for ( ; idx <= N; idx += (idx & -idx))
            bit[idx] += val;
    }

    LL query(int idx) {
        LL result = 0;

        for ( ; idx > 0; idx -= (idx & -idx))
            result += bit[idx];

        return result;
    }

    LL rsq(int a, int b) {
        return query(b) - query(a - 1);
    }
};

int main() {
    int T, N, Q, A[MAXN + 3];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &Q);

        BIT stair = BIT(N);
        BIT bit = BIT(N);

        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);

            int mult = (i % 2 == 0 ? -1 : 1);
            stair.update(i, mult * i * A[i]);
            bit.update(i, mult * A[i]);
        }

        LL answer = 0;
        for (int i = 1; i <= Q; i++) {
            char typ[2];
            scanf("%s", typ);

            if (typ[0] == 'U') {
                int idx, a;
                scanf("%d%d", &idx, &a);

                int mult = (idx % 2 == 0 ? -1 : 1);
                stair.update(idx, mult * idx * (a - A[idx]));
                bit.update(idx, mult * (a - A[idx]));

                A[idx] = a;
            } else {
                int l, r;
                scanf("%d%d", &l, &r);

                LL result = stair.rsq(l, r) - bit.rsq(l, r)*(l - 1);
                if (l % 2 == 0)
                    result = -result;

                answer += result;
            }
        }

        printf("Case #%d: %lld\n", cases, answer);
    }
}
