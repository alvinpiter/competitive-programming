#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 50000
#define MAXA 100000

int N, parent[MAXN + 3];
vector<int> who[MAXA + 3];
LL answer;

int findSet(int u) {
    return (parent[u] == u ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void joinSet(int u, int v) {
    parent[findSet(u)] = findSet(v);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int number;
        scanf("%d", &number);

        for (int div = 1; div * div <= number; div++) {
            if (number%div == 0) {
                who[div].push_back(i);
                if (div * div != number)
                    who[number/div].push_back(i);
            }
        }
    }

    answer = 0;
    for (int i = 1; i <= N; i++)
        parent[i] = i;

    for (int i = MAXA; i >= 1; i--) {
        for (int j = 1; j < who[i].size(); j++) {
            int a = who[i][j - 1];
            int b = who[i][j];
            if (!isSameSet(a, b)) {
                answer += i;
                joinSet(a, b);
            }
        }
    }

    printf("%lld\n", answer);
}
