#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, a[103], l, r, answer;

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    l = 1;
    r = n;
    answer = 0;
    while (l <= r) {
        if (a[l] <= k) {
            l += 1;
            answer += 1;
        } else if (a[r] <= k) {
            r -= 1;
            answer += 1;
        } else {
            break;
        }
    }

    cout << answer << endl;
}
