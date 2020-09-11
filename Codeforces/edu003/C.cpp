#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m[100003], sum, mini, maxi, cntMaxi, answer;

    cin >> n;

    sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
        sum += m[i];
    }

    mini = sum/n;
    maxi = sum/n + (sum % n == 0 ? 0 : 1);

    cntMaxi = sum%n;

    sort(m + 1, m + n + 1);

    answer = 0;
    for (int i = 1; i <= n - cntMaxi; i++) {
        answer += max(0, m[i] - mini);
    }

    for (int i = n - cntMaxi + 1; i <= n; i++) {
        answer += max(0, m[i] - maxi);
    }

    cout << answer << endl;
}
