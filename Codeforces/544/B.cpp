#include<bits/stdc++.h>
using namespace std;

int n, k, d, counter[103], answer;

int main() {
    cin >> n >> k;

    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < n; i++) {
        cin >> d;
        counter[d%k] += 1;
    }

    answer = counter[0] - counter[0]%2;

    int l = 1, r = k - 1;

    while (r > l) {
        answer += 2 * min(counter[l], counter[r]);
        l += 1;
        r -= 1;
    }

    if (l == r)
        answer += counter[l] - counter[l]%2;

    cout << answer << endl;
}
