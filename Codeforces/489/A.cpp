#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    set<int> s;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;

        if (num != 0)
            s.insert(num);
    }

    cout << (int) s.size() << endl;
}
