#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Note: we can take more than n red balls if a + c <= n.
*/

int main() {
    LL a, b, c, n, m;

    cin >> a >> b >> c >> n >> m;

    LL lo = 0, hi = a + b + c, mid;

    while (hi >= lo) {
        mid = (lo + hi)/2;

        LL maxRed = (a + c <= n ? a + b + c : n);
        LL maxGreen = (b + c <= m ? a + b + c : m);

        if (mid < maxRed && mid < maxGreen)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    cout << lo << endl;
}
