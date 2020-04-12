#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a;
    bool marked[103];

    cin >> n;

    memset(marked, false, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        cin >> a;
        marked[a] = true;
    }

    int answer = 0;
    for (int i = 1; i <= 100; i++) {
        if (marked[i] == true) {
            answer += 1;
            for (int j = 2 * i; j <= 100; j += i)
                marked[j] = false;
        }
    }

    cout << answer << endl;
}
