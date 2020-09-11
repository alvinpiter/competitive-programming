#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, k;
LL psum[200003];
pair<LL, int> bestb[200003]; //{score, idx}

int main() {
    scanf("%d%d", &n, &k);

    psum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int num;
        scanf("%d", &num);

        psum[i] = psum[i - 1] + num;
    }

    bestb[n - k + 1] = {psum[n] - psum[n - k], n - k + 1};
    for (int b = n - k; b >= 1; b--) {
        pair<LL, int> curr = {psum[b + k - 1] - psum[b - 1], b};
        if (curr.first >= bestb[b + 1].first)
            bestb[b] = curr;
        else
            bestb[b] = bestb[b + 1];
    }

    LL maxScore = 0;
    int a, b;
    for (int i = 1; i + 2*k - 1 <= n; i++) {
        LL score = (psum[i + k - 1] - psum[i - 1]) + bestb[i + k].first;
        if (score > maxScore) {
            maxScore = score;
            a = i;
            b = bestb[i + k].second;
        }
    }

    printf("%d %d\n", a, b);
}
