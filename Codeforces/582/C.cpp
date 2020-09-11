#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int q, seen[10];
LL n, m;
vector<int> patterns;

int main() {
    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%lld%lld", &n, &m);

        patterns.clear();
        memset(seen, -1, sizeof(seen));
        for (int mul = 1; mul <= 10; mul++) {
            int num = (m*mul)%10;
            if (seen[num] == 1)
                break;

            seen[num] = 1;
            patterns.push_back(num);
        }

        int sumAll = 0;
        for (int i = 0; i < patterns.size(); i++)
            sumAll += patterns[i];

        LL remainderCount = n/m;
        LL cycleCount = remainderCount/patterns.size();
        LL remCount = remainderCount%patterns.size();

        int sumRemainder = 0;
        for (int i = 0; i < remCount; i++)
            sumRemainder += patterns[i];

        cout << cycleCount * sumAll + sumRemainder << endl;
    }
}
