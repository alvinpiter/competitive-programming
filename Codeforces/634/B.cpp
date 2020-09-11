#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a, b;
    string answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> a >> b;
        for (int i = 0; i < n; i++)
            cout << (char) (i%b + 'a');

        cout << endl;
    }
}
