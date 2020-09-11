#include<bits/stdc++.h>
using namespace std;
#define LL long long int

//how many times power of p can be used
int calc(int p) {
    for (int i = 1; ; i++) {
        if (i > p)
            return i - 1;
        else
            p -= i;
    }
}

int main() {
    LL N;
    int ans;

    cin >> N;

    ans = 0;
    for (LL div = 2; div * div <= N; div++) {
        if (N % div == 0) {
            int cnt = 0;
            while (N % div == 0) {
                cnt += 1;
                N /= div;
            }

            ans += calc(cnt);
        }
    }

    if (N != 1)
        ans += calc(1);

    cout << ans << endl;
}
