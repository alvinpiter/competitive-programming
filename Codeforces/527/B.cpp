#include<bits/stdc++.h>
using namespace std;

int n, a[103], answer;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);

    answer = 0;
    for (int i = 1; i < n; i += 2) {
        if (a[i] != a[i - 1])
            answer += (a[i] - a[i - 1]);
    }

    cout << answer << endl;
}
