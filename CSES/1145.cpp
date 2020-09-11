#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> m; //m[i] -> smallest integer x such that there is an increasing subsequence of length i ending at x

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        int pos = lower_bound(m.begin(), m.end(), x) - m.begin();
        if (pos == m.size())
            m.push_back(x);
        else
            m[pos] = x;
    }

    printf("%d\n", (int) m.size());
}
