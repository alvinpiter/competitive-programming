#include<bits/stdc++.h>
using namespace std;
#define MAXM 200000
#define MAXK 200000
#define MAXA 200000

struct Trap {
    int l, r, d;
    Trap() {}
    Trap(int _l, int _r, int _d): l(_l), r(_r), d(_d) {}
};

bool compareTrap(Trap a, Trap b) {
    return a.l < b.l;
}

int M, N, K, T, A[MAXM + 3];
Trap traps[MAXK + 3];

int main() {
    scanf("%d%d%d%d", &M, &N, &K, &T);
    for (int i = 0; i < M; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < K; i++) {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);

        traps[i] = Trap(l, r, d);
    }

    sort(traps, traps + K, compareTrap);

    int lo, mid, hi;

    lo = 1;
    hi = MAXA;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        vector<Trap> curTraps;
        for (int i = 0; i < K; i++) {
            if (mid < traps[i].d)
                curTraps.push_back(traps[i]);
        }

        vector<int> once, thrice;
        int lastR = 0;
        for (int i = 0; i < curTraps.size();) {
            once.push_back((curTraps[i].l - 1) - lastR);
            lastR = curTraps[i].l - 1;

            int maxR = curTraps[i].r;
            int j;
            for (j = i; j < curTraps.size(); j++) {
                if (curTraps[j].l > maxR) {
                    break;
                } else {
                    maxR = max(maxR, curTraps[j].r);
                }
            }

            thrice.push_back(maxR - lastR);
            lastR = maxR;

            i = j;
        }

        once.push_back(N + 1 - lastR);

        int totalTime = 0;
        for (int i = 0; i < once.size(); i++) totalTime += once[i];
        for (int i = 0; i < thrice.size(); i++) totalTime += 3 * thrice[i];

        if (totalTime <= T)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    //Count how many soldiers with agility at least lo
    int answer = 0;
    for (int i = 0; i < M; i++) {
        if (A[i] >= lo)
            answer += 1;
    }

    printf("%d\n", answer);
}
