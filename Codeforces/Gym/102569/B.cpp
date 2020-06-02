#include<bits/stdc++.h>
using namespace std;

int n, t, zero, answer;
vector<int> pos, neg;

int main() {
    scanf("%d%d", &n, &t);

    zero = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        if (x == 0)
            zero = 1;
        else if (x < 0)
            neg.push_back(x);
        else
            pos.push_back(x);
    }

    reverse(neg.begin(), neg.end());

    answer = 0;

    //take x > 0, then x < 0
    for (int cntPos = 0; cntPos <= (int) pos.size(); cntPos++) {
        int lastPosition = (cntPos == 0 ? 0 : pos[cntPos - 1]);
        int timeLeft = t - lastPosition;

        if (timeLeft < 0)
            break;

        int lo = 0, hi = (int) neg.size() - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (lastPosition - neg[mid] > timeLeft)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        answer = max(answer, zero + cntPos + (hi + 1));
    }

    //take x < 0 then x > 0
    for (int cntNeg = 0; cntNeg <= (int) neg.size(); cntNeg++) {
        int lastPosition = (cntNeg == 0 ? 0 : neg[cntNeg - 1]);
        int timeLeft = t - abs(lastPosition);

        if (timeLeft < 0)
            break;

        int lo = 0, hi = (int) pos.size() - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (pos[mid] - lastPosition > timeLeft)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        answer = max(answer, zero + cntNeg + (hi + 1));
    }

    printf("%d\n", answer);
}
