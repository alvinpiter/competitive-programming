#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, N, A[200003];

    cin >> K >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    int maxi = 0;
    for (int i = 2; i <= N; i++)
        maxi = max(maxi, A[i] - A[i - 1]);

    maxi = max(maxi, K - A[N] + A[1]);

    cout << K - maxi << endl;
}
