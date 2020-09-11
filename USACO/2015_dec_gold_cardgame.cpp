#include<bits/stdc++.h>
using namespace std;
#define MAXN 50000

int N, elsie[MAXN + 3], answer;
bool used[2 * MAXN + 3];
set<int> bessieHigh, bessieLow;

int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> elsie[i];
        used[elsie[i]] = true;
    }

    for (int i = 1; i <= 2 * N && bessieLow.size() < N/2; i++) {
        if (!used[i]) {
            bessieLow.insert(i);
            used[i] = true;
        }
    }

    for (int i = 1; i <= 2 * N; i++) {
        if (!used[i]) {
            bessieHigh.insert(i);
        }
    }

    answer = 0;
    for (int i = 1; i <= N/2; i++) {
        auto lb = bessieHigh.lower_bound(elsie[i]);
        if (lb != bessieHigh.end()) {
            answer += 1;
            bessieHigh.erase(lb);
        }
    }

    for (int i = N/2 + 1; i <= N; i++) {
        auto lb = bessieLow.lower_bound(elsie[i]);
        if (lb != bessieLow.begin()) {
            answer += 1;
            bessieLow.erase(--lb);
        }
    }

    cout << answer << endl;
}
