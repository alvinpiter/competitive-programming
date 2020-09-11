#include<bits/stdc++.h>
using namespace std;
#define MAXN 150000

int n, a[MAXN + 3];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);

    int largestInTeam = 0, answer = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 1 && a[i] - 1 > largestInTeam) {
            largestInTeam = a[i] - 1;
            answer += 1;
        } else if (a[i] > largestInTeam) {
            largestInTeam = a[i];
            answer += 1;
        } else if (a[i] + 1 > largestInTeam) {
            largestInTeam = a[i] + 1;
            answer += 1;
        }
    }

    cout << answer << endl;
}
