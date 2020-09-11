#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int n, a[MAXN + 3], b[MAXN + 3];
vector<int> diff;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = 0; i < n; i++) diff.push_back(a[i] - b[i]);

    sort(diff.begin(), diff.end());

    LL answer = 0;
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(diff.begin() + i + 1, diff.end(), -diff[i] + 1) - diff.begin();
        answer += (n - pos);
    }

    cout << answer << endl;
}
