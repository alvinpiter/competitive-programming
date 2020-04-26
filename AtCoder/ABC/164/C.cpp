#include<bits/stdc++.h>
using namespace std;

int main() {
    set<string> sets;
    int n;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        sets.insert(s);
    }

    cout << (int) sets.size() << endl;
}
