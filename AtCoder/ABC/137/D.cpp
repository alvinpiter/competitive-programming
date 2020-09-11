#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, answer;
pair<int, int> jobs[MAXN + 3];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int a, b;
        cin >> a >> b;

        jobs[i] = {a, b};
    }

    sort(jobs + 1, jobs + N + 1);

    answer = 0;
    priority_queue<int> pq;

    int ptr = 0;
    for (int day = M; day >= 0; day--) {
        while (ptr <= N && jobs[ptr].first <= M - day) {
            pq.push(jobs[ptr].second);
            ptr += 1;
        }

        if (!pq.empty()) {
            answer += pq.top();
            pq.pop();
        }
    }

    cout << answer << endl;
}
