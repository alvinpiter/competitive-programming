#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000

int n, a[MAXN + 3];
LL result;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    sort(a + 1, a + n + 1);

    int l = 1, r = n;
    result = 0;

    while (r > l) {
        int sum = (a[l] + a[r]);
        if (n%2 == 1 && r - l == 2)
            sum += a[l + 1];

        result += sum * sum;

        l += 1;
        r -= 1;
    }

    cout << result << endl;
}
