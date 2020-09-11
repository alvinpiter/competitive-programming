#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000

int N, Q, A[MAXN + 3];
LL result;

int main() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    result = 0;
    for (int bit = 0; bit < 31; bit++) {
        LL num0 = 0, num1 = 0;
        for (int i = 1; i <= N; i++) {
            if (A[i] & (1 << bit))
                num1 += 1;
            else
                num0 += 1;
        }

        for (int i = 1; i <= Q; i++) {
            LL temp0 = num0*num0 + num1*num1;
            LL temp1 = 2*num0*num1;

            num0 = temp0%MOD;
            num1 = temp1%MOD;
        }

        result = (result + ((1LL << bit)*num1)%MOD)%MOD;
    }

    cout << result << endl;
}
