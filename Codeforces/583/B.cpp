#include<bits/stdc++.h>
using namespace std;

int b, g, n, answer;

int main() {
    cin >> b >> g >> n;

    answer = 0;
    for (int i = 0; i <= n; i++) {
        if (i <= b && n - i <= g)
            answer += 1;
    }

    cout << answer << endl;
}
