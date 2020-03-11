#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, p[22];
LL mini;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i];

    mini = 1e12;
    for (int mask = 0; mask < (1 << n); mask++) {
        LL first = 0, second = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                first += p[i];
            else
                second += p[i];
        }

        mini = min(mini, abs(first - second));
    }

    cout << mini << endl;
}
