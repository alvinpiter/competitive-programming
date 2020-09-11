#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, p[2003];

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i];

    sort(p, p + n);

    int sum = 0;
    int answer = 1;
    for (int i = 0; i < n - 1; i++) {
        if (sum + p[i] <= p[n - 1]) {
            sum += p[i];
            answer += 1;
        }
    }

    cout << answer << endl;

}
