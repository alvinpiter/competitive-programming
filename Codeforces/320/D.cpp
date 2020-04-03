#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, K, a[MAXN + 3];
LL X, mul, prefixOR[MAXN + 3], suffixOR[MAXN + 3];

int main() {
    cin >> N >> K >> X;

    mul = 1;
    for (int i = 1; i <= K; i++) mul *= X;

    for (int i = 1; i <= N; i++)
        cin >> a[i];

    prefixOR[0] = 0;
    for (int i = 1; i <= N; i++)
        prefixOR[i] = prefixOR[i - 1] | a[i];

    suffixOR[N + 1] = 0;
    for (int i = N; i >= 1; i--)
        suffixOR[i] = suffixOR[i + 1] | a[i];

    LL maxi = 0;
    for (int i = 1; i <= N; i++)
        maxi = max(maxi, prefixOR[i - 1] | (a[i] * mul) | suffixOR[i + 1]);

    cout << maxi << endl;
}
