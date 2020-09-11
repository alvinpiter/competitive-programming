#include<bits/stdc++.h>
using namespace std;

int n, a[200003], b[200003];
map<pair<int, pair<int, int> >, int> counter;

void add(pair<int, pair<int, int> > p) {
    if (counter.find(p) == counter.end())
        counter[p] = 1;
    else
        counter[p] += 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cin >> b[i];

    int dCanBeAnything = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (b[i] == 0)
                dCanBeAnything += 1;
        } else {
            int sign, aa, bb, g;

            aa = abs(a[i]);
            bb = abs(b[i]);
            g = __gcd(aa, bb);
            aa /= g;
            bb /= g;
            if (a[i] > 0) {
                if (b[i] < 0) {
                    add({-1, {bb, aa}});
                } else if (b[i] == 0) {
                    add({0, {0, 0}});
                } else if (b[i] > 0) {
                    add({1, {bb, aa}});
                }
            } else {
                if (b[i] < 0) {
                    add({1, {bb, aa}});
                } else if (b[i] == 0) {
                    add({0, {0, 0}});
                } else if (b[i] > 0) {
                    add({-1, {bb, aa}});
                }
            }
        }
    }

    int answer = 0;
    for (map<pair<int, pair<int, int> >, int>::iterator it = counter.begin(); it != counter.end(); ++it) {
        answer = max(answer, it->second);
    }

    cout << answer + dCanBeAnything << endl;
}
