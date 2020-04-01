#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL solve(LL h) {
    if (h == 0)
        return 0;

    return 1 + 2 * solve(h/2);
}

int main() {
    LL H;
    cin >> H;

    cout << solve(H) << endl;
}
