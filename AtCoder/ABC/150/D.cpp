#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int N, M, cnt2;
LL a, LCM;

int count2(int num) {
    int result = 0;
    while (num % 2 == 0) {
        result += 1;
        num /= 2;
    }

    return result;
}

int main() {
    cin >> N >> M;

    cin >> a;
    a /= 2;

    LCM = a;

    cnt2 = count2(a);

    for (int i = 2; i <= N; i++) {
        cin >> a;
        a /= 2;

        LCM = (a * LCM)/__gcd(a, LCM);

        if (count2(a) != cnt2 || LCM > M) {
            cout << 0 << endl;
            return 0;
        }
    }

    int ans = M/LCM;
    cout << (ans + 1)/2 << endl;
}
