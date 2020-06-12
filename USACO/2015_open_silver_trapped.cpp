#include<bits/stdc++.h>
using namespace std;
#define INF 2000000001
#define MAXN 100000

int N, B, L[MAXN + 3], R[MAXN + 3];
pair<int, int> haybales[MAXN + 3]; //{pos, size}

int main() {
    freopen("trapped.in", "r", stdin);
    freopen("trapped.out", "w", stdout);

    cin >> N >> B;
    for (int i = 1; i <= N; i++)
        cin >> haybales[i].second >> haybales[i].first;

    sort(haybales + 1, haybales + N + 1);

    int idx; //first haybale to the right of Bessie
    for (int i = 1; i <= N; i++) {
        if (haybales[i].first > B) {
            idx = i;
            break;
        }
    }

    int answer = INF;

    int lastL = idx;

    //treat i-th haybale as the rightmost haybale that can't be passed
    for (int i = idx; i <= N; i++) {
        while (lastL > 1 && haybales[lastL - 1].second < haybales[i].first - haybales[lastL - 1].first)
            lastL -= 1;

        if (lastL == 1)
            break;

        answer = min(answer, max(0, haybales[i].first - haybales[lastL - 1].first - haybales[i].second));

        if (haybales[i].first - haybales[lastL - 1].first <= haybales[i].second)
            break;
    }

    int lastR = idx - 1;

    //treat i-th haybale as the leftmost haybale that can't be passed
    for (int i = idx - 1; i >= 1; i--) {
        while (lastR < N && haybales[lastR + 1].second < haybales[lastR + 1].first - haybales[i].first)
            lastR += 1;

        if (lastR == N)
            break;

        answer = min(answer, max(0, haybales[lastR + 1].first - haybales[i].first - haybales[i].second));

        if (haybales[lastR + 1].first - haybales[i].first <= haybales[i].second)
            break;
    }

    if (answer < INF)
        cout << answer << endl;
    else
        cout << -1 << endl;
}
