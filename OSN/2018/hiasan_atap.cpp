#include<bits/stdc++.h>
using namespace std;
#define MAXS 100000
#define LL long long int

int K, Q;
int lenS, countL, countR, height[MAXS + 3];
LL N, peakPos, peakHeight;
string dummy, S;

void precompute() {
    lenS = S.length();
    N = (LL) K * lenS + 1;

    countL = countR = 0;
    memset(height, 0, sizeof(0));

    int L = 1, R = lenS + 1;
    for (int i = 0; i < lenS; i++) {
        if (S[i] == 'A') {
            height[L] += 1;
            height[R] -= 1;
            R -= 1;
            countL += 1;
        } else {
            height[L + 1] += 1;
            height[R + 1] -= 1;
            L += 1;
            countR += 1;
        }
    }

    for (int i = 1; i <= lenS + 1; i++)
        height[i] += height[i - 1];

    peakPos = 1 + (LL) K * countR;
    peakHeight = (LL) K * lenS + 1;
}

LL getHeightLeft(LL pos) {
    LL numCycle = (pos - 1)/countR;
    LL rem = (pos - 1)%countR;
    LL result = numCycle * lenS + height[rem + 1] + 1;

    return result;
}

LL getHeightRight(LL pos) {
    LL numCycle = (N - pos)/countL;
    LL rem = (N - pos)%countL;
    LL result = numCycle * lenS + height[(lenS + 1) - rem] + 1;

    return result;
}

LL query(LL l, LL r) {
    if (r < peakPos)
        return getHeightLeft(r);

    if (l > peakPos)
        return getHeightRight(l);

    return peakHeight;
}

int main() {
    cin >> dummy;
    cin >> S;
    cin >> K >> Q;

    precompute();

    for (int i = 1; i <= Q; i++) {
        LL l, r;

        cin >> l >> r;
        cout << query(l, r) << endl;
    }
}
