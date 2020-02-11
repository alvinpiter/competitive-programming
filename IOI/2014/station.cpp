#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

int N, K, stations[MAXN + 3], nxt[MAXN + 3];
queue<int> Q;

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> stations[i];

    for (int i = N; i >= 1; i--) {
        while (!Q.empty() && Q.front() - i > K)
            Q.pop();

        if (Q.empty())
            nxt[i] = -1;
        else
            nxt[i] = Q.front();

        if (stations[i] == 1)
            Q.push(i);
    }

    int answer = 0;
    int current = 1;
    while (nxt[current] != -1) {
        answer += 1;
        current = nxt[current];
    }

    if (current == N)
        cout << answer << endl;
    else
        cout << "-1\n";
}
