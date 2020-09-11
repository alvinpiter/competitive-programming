#include<bits/stdc++.h>
using namespace std;

int n, a[200003], answer;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);

    answer = 1;
    for (int i = 0; i < n; i++) {
        int p = upper_bound(a, a + n, a[i] + 5) - a;
        answer = max(answer, p - i);
    }

    cout << answer << endl;
}
