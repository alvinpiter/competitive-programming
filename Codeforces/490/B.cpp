#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;

    cin >> n >> s;
    for (int d = 1; d <= n; d++) {
        if (n % d == 0) {
            int l = 0;
            int r = d - 1;

            while (l < r) {
                swap(s[l], s[r]);
                l += 1;
                r -= 1;
            }
        }
    }

    cout << s << endl;
}
