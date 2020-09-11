#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXLG 60
#define MOD 1000000007

int N, count1[MAXLG + 3];

int main() {
    cin >> N;

    memset(count1, 0, sizeof(count1));
    for (int i = 1; i <= N; i++) {
        LL A;
        cin >> A;

        for (int lg = 0; lg <= MAXLG; lg++) {
            if (A & (1LL << lg))
                count1[lg] += 1;
        }
    }

    LL answer = 0;
    for (int lg = 0; lg <= MAXLG; lg++) {
        int count0 = N - count1[lg];

        LL temp1 = ((LL) count0 * count1[lg])%MOD;
        LL temp2 = (1LL << lg)%MOD;
        answer = (answer + (temp1 * temp2)%MOD)%MOD;
    }

    cout << answer << endl;
}
