#include<bits/stdc++.h>
using namespace std;

/*
Observe that we can make the cost to be 0 by setting:
d1 = n - 1
d2 = n - 2
d3 = n - 3
.
.
dn_1 = 1
dn = anything (since it will be multiplied by 0 anyway)

To construct the solution, group d1, d3, d5, .. and group d2, d4, .. and lastly append n in the end.
*/

void printVector(vector<int>& v) {
    for (auto x: v)
        cout << x << " ";
}

int main() {
    int n;
    vector<int> odds, evens;

    cin >> n;
    if (n == 1) {
        cout << 1 << " " << 1 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i += 2) {
        odds.push_back(i);
    }

    for (int i = 2; i <= n; i += 2) {
        evens.push_back(i);
    }

    printVector(odds);

    if (odds.back() == n)
        odds.pop_back();

    reverse(odds.begin(), odds.end());
    printVector(odds);

    printVector(evens);

    if (evens.back() == n)
        evens.pop_back();

    reverse(evens.begin(), evens.end());
    printVector(evens);

    cout << n << endl;
}
