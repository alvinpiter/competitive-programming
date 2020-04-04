#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define DEPTH 10

vector<LL> lunlun;

void generate(LL current, int depth) {
    lunlun.push_back(current);

    if (depth == DEPTH)
        return;

    int last = current%10;

    generate(10 * current + last, depth + 1);
    if (last > 0) generate(10 * current + last - 1, depth + 1);
    if (last < 9) generate(10 * current + last + 1, depth + 1);
}

int main() {
    for (int i = 1; i <= 9; i++)
        generate(i, 1);

    sort(lunlun.begin(), lunlun.end());
    lunlun.resize(distance(lunlun.begin(), unique(lunlun.begin(), lunlun.end())));

    int K;
    scanf("%d", &K);
    printf("%lld\n", lunlun[K - 1]);
}
