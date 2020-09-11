#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N, M, l[MAXN + 3];
LL p[MAXN + 3], shifts[MAXN + 3];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
        cin >> l[i];

    //Lay the strips back to back
    p[1] = 1;
    for (int i = 2; i <= M; i++)
        p[i] = p[i - 1] + l[i - 1];

    //If total length of the strips can't cover all the cells
    if (p[M] + l[M] - 1 < N) {
        cout << -1 << endl;
        return 0;
    }

    LL needToShift = (p[M] + l[M] - 1) - N;

    shifts[0] = shifts[1] = 0;
    for (int i = 2; i <= M; i++) {
        LL shift = min((LL) l[i - 1] - 1, needToShift);

        needToShift -= shift;
        shifts[i] = shift;
    }

    //Aggregate the shift and update position of strips
    for (int i = 1; i <= M; i++) {
        shifts[i] += shifts[i - 1];
        p[i] = p[i] - shifts[i];

        //This strip is too long
        if (p[i] + l[i] - 1 > N) {
            cout << -1 << endl;
            return 0;
        }
    }

    for (int i = 1; i <= M; i++)
        cout << p[i] << " ";
    cout << endl;
}
