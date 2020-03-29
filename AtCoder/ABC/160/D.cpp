#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, X, Y, cnt[2003];

    cin >> N >> X >> Y;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int d = abs(i - j); //goes straight

            d = min(d, abs(i - X) + 1 + abs(Y - j)); //goes to X then Y then j
            d = min(d, abs(i - Y) + 1 + abs(X - j)); //goes to Y then X then j

            cnt[d] += 1;
        }
    }

    for (int i = 1; i < N; i++)
        cout << cnt[i] << endl;
}
