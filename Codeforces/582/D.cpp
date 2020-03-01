#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, k, answer;
vector<int> costs[MAXN + 3];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int number;
        scanf("%d", &number);

        int cost = 0;
        while (true) {
            costs[number].push_back(cost);

            if (number == 0)
                break;

            number /= 2;
            cost += 1;
        }
    }

    answer = 1e9;
    for (int i = 0; i <= MAXN; i++) {
        if (costs[i].size() >= k) {
            sort(costs[i].begin(), costs[i].end());

            int sum = 0;
            for (int j = 0; j < k; j++)
                sum += costs[i][j];

            answer = min(answer, sum);
        }
    }

    printf("%d\n", answer);
}
