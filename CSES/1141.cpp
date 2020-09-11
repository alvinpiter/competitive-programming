#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, k[MAXN + 3], ptr, answer;
map<int, int> counter;

int main() {
    scanf("%d", &n);

    answer = 1;
    ptr = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);

        if (counter.find(k[i]) != counter.end())
            counter[k[i]] += 1;
        else
            counter[k[i]] = 1;

        while (counter[k[i]] == 2) {
            counter[k[ptr]] -= 1;
            ptr += 1;
        }

        answer = max(answer, i - ptr + 1);
    }

    printf("%d\n", answer);
}
