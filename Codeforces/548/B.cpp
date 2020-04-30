#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n, a[MAXN + 3], last;
    long long int answer;

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    answer = a[n];
    last = a[n];

    for (int i = n - 1; i >= 1; i--) {
        int take = min(last - 1, a[i]);
        take = max(take, 0);

        answer += take;
        last = take;
    }

    cout << answer << endl;
}
