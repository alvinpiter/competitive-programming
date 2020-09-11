#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int N, L[MAXN + 3], R[MAXN + 3], A[MAXN + 3];
LL sumL, sumR;

int main() {
    cin >> N;

    sumL = 0;
    for (int i = 1; i <= N; i++) {
        cin >> L[i];
        sumL += L[i];

        A[i] = L[i];
    }

    sumR = 0;
    for (int i = 1; i <= N; i++) {
        cin >> R[i];
        sumR += R[i];
    }

    bool canBeLargerThanSumL = false;
    for (int i = 1; i <= N; i++) {
        if (L[i] < R[i]) {
            A[i] += 1;
            canBeLargerThanSumL = true;
            break;
        }
    }

    if (canBeLargerThanSumL) {
        bool canBeSmallerThanSumR = false;
        for (int i = 1; i <= N; i++) {
            if (A[i] < R[i])
                canBeSmallerThanSumR = true;
        }

        if (canBeLargerThanSumL && canBeSmallerThanSumR) {
            for (int i = 1; i <= N; i++) {
                if (i > 1)
                    cout << " ";

                cout << A[i];
            }
            cout << endl;
        } else
            cout << "-1\n";
    } else {
        cout << "-1\n";
    }
}
