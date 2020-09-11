#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000

int N, M;
long long int totalCost;
vector<int> answer;

int main() {
    cin >> N >> M;

    queue<int> Q;
    map<int, int> dist;

    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;

        Q.push(x);
        dist[x] = 0;
    }

    totalCost = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();

        if (answer.size() == M)
            break;

        if (u - 1 >= -INF && dist.find(u - 1) == dist.end()) {
            answer.push_back(u - 1);

            dist[u - 1] = dist[u] + 1;
            totalCost += dist[u - 1];
            Q.push(u - 1);
        }

        if (answer.size() == M)
            break;

        if (u + 1 <= INF && dist.find(u + 1) == dist.end()) {
            answer.push_back(u + 1);

            dist[u + 1] = dist[u] + 1;
            totalCost += dist[u + 1];
            Q.push(u + 1);
        }
    }

    cout << totalCost << endl;
    for (auto ans: answer)
        cout << ans << " ";

    cout << endl;
}
