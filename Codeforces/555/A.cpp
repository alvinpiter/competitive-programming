#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, answer;
    set<int> visited;

    cin >> n;

    visited.insert(n);
    while (n > 0) {
        n += 1;

        while (n % 10 == 0)
            n /= 10;

        if (visited.find(n) != visited.end())
            break;
        else
            visited.insert(n);
    }

    cout << visited.size() << endl;
}
