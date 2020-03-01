#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, answer;
LL g;

int main() {
    cin >> n;

    g = 0;
    for (int i = 1; i <= n; i++) {
        LL num;
        cin >> num;

        g = __gcd(num, g);
    }

    answer = 0;
    for (LL div = 1; div * div <= g; div++) {
        if (g % div == 0) {
            if (div * div == g)
                answer += 1;
            else
                answer += 2;
        }
    }

    cout << answer << endl;
}
