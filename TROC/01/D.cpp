#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int N, A[MAXN + 3], minSize;
LL sum;

bool check(int X) {
    int last = -1;
    for (int i = 1; i <= N; i++) {
        if (i + A[i] < X + 1) {
            if (last != -1) {
                if (last != i - 1)
                    return false;
                else {
                    int lnow = A[i] + 1;
                    int rnow = (X + 1) - i;

                    int lprev = A[i - 1] + 1;
                    int rprev = (X + 1) - (i - 1);

                    if (rnow < lprev || lnow > rprev)
                        return false;
                }
            }

            last = i;
        }
    }

    if (last == -1)
        return true;

    if (X > N) {
        if (last != N)
            return false;

        int lnow = 1;
        int rnow = (X + 1) - (N + 1);

        int lprev = A[N] + 1;
        int rprev = (X + 1) - N;

        if (rnow < lprev || lnow > rprev)
            return false;
    }

    return true;
}

int main() {
    memset(A, 0, sizeof(A));

    cin >> N;

    sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        sum += A[i];
    }

    minSize = 0;
    for (int i = 1; i <= N; i++)
        minSize = max(minSize, i + A[i] - 1);

    for (int i = 0; i < 3; i++) {
        if (check(minSize + i)) {
            LL sz = (LL) minSize + i;
            LL all = (sz * sz + sz)/2;

            cout << all - sum << endl;
            break;
        }
    }
}


/*
Y
YY
XXY
YYYY
XXXXX

3
5 0 2

3
5 4 2
Y
YY
YYY
XXYY
XXXXY
XXXXXY
*/
