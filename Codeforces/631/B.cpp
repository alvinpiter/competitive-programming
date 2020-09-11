#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int t, n, a[MAXN + 3], maxi;
bool seen[MAXN + 3];
vector<pair<int, int> > answer;

//Check if indices l to r of array a is a permutation of r - l + 1 elements
bool validate(int l, int r) {
    for (int i = 1; i <= r - l + 1; i++)
        seen[i] = false;

    for (int i = l; i <= r; i++)
        seen[a[i]] = true;

    for (int i = 1; i <= r - l + 1; i++) {
        if (seen[i] == false)
            return false;
    }

    return true;
}

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        maxi = 1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            maxi = max(maxi, a[i]);
        }

        answer.clear();

        if (validate(1, maxi) && validate(maxi + 1, n))
            answer.push_back({maxi, n - maxi});

        if (validate(1, n - maxi) && validate(n - maxi + 1, n) && maxi * 2 != n)
            answer.push_back({n - maxi, maxi});

        cout << answer.size() << endl;
        for (auto a: answer)
            cout << a.first << " " << a.second << endl;
    }
}
