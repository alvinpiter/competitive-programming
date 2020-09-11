#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n, k, m[MAXN + 3], c[MAXN + 3];

    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> m[i];

    for (int i = 0; i < k; i++)
        cin >> c[i];

    sort(m, m + n);

    int numGroup = 0;
    int ptr = n - 1;
    for (int j = k; j >= 1; j--) {
        while (ptr >= 0 && m[ptr] >= j)
            ptr -= 1;

        int cnt = n - ptr - 1;
        numGroup = max(numGroup, cnt/c[j - 1] + (cnt%c[j - 1] == 0 ? 0 : 1));
    }

    vector<int> group[numGroup];
    for (int i = n - 1; i >= 0; i--)
        group[(n - i - 1)%numGroup].push_back(m[i]);

    cout << numGroup << endl;
    for (int g = 0; g < numGroup; g++) {
        cout << group[g].size();
        for (int i = 0; i < group[g].size(); i++)
            cout << " " << group[g][i];

        cout << endl;
    }
}
