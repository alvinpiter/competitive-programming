#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

/*
For each index i:
* Find the index of the first 2 larger number to the right of it
* Find the index of the first 2 larger number to the left of it

It can be done by processing number from large to small and maintain their indices in a set.

Then do contribution technique.
*/

int main() {
    /*
    right1[i] -> smallest j (j > i) such that P[j] > P[i]
    right2[i] -> second smallest j (j > i) such that P[j] > P[i];

    left1 and left2 defined similarly
    */

    int N, P[MAXN + 3], pos[MAXN + 3];
    int right1[MAXN + 3], right2[MAXN + 3], left1[MAXN + 3], left2[MAXN + 3];

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> P[i];
        pos[P[i]] = i;
    }

    set<int> active;
    active.insert(0);
    active.insert(N + 1);

    //process from larger
    for (int num = N; num >= 1; num--) {
        int p = pos[num];

        auto rightPtr = active.lower_bound(p);

        right1[p] = *rightPtr;
        right2[p] = (right1[p] == N + 1 ? N + 1 : *(++rightPtr));

        auto leftPtr = active.lower_bound(p);
        --leftPtr;

        left1[p] = *leftPtr;
        left2[p] = (left1[p] == 0 ? 0 : *(--leftPtr));

        active.insert(p);
    }

    LL answer = 0;
    for (int i = 1; i <= N; i++) {
        if (right1[i] != N + 1) {
            int cntLeft = i - left1[i];
            int cntRight = right2[i] - right1[i];

            answer += (LL) P[i] * cntLeft * cntRight;
        }

        if (left1[i] != 0) {
            int cntLeft = left1[i] - left2[i];
            int cntRight = right1[i] - i;

            answer += (LL) P[i] * cntLeft * cntRight;
        }
    }

    cout << answer << endl;
}
