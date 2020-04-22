#include<bits/stdc++.h>
using namespace std;

int n, k, a[300005], answer;
vector<int> diffs;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (i > 1) {
            diffs.push_back(a[i] - a[i - 1]);
        }
    }

    sort(diffs.begin(), diffs.end(), greater<int>());

    answer = a[n] - a[1];
    for (int i = 0; i < k - 1; i++)
        answer -= diffs[i];

    printf("%d\n", answer);
}
