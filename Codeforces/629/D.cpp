#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int q, n, t[MAXN + 3], color[MAXN + 3];
set<int> types;

int main() {
    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        types.clear();

        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> t[i];
            types.insert(t[i]);
        }

        if (types.size() == 1) {
            for (int i = 0; i < n; i++)
                color[i] = 1;
        } else if (types.size() == 2) {
            for (int i = 0; i < n; i++)
                color[i] = (t[i] == t[0] ? 1 : 2);
        } else {
            if (n % 2 == 0) {
                for (int i = 0; i < n; i++)
                    color[i] = i % 2 + 1;
            } else {
                int current = -1;
                for (int i = 0; i < n; i++) {
                    if (t[i] == t[(i + 1)%n]) {
                        current = (i + 1)%n;
                        break;
                    }
                }

                if (current == -1) {
                    for (int i = 0; i < n - 1; i++)
                        color[i] = i%2 + 1;

                    color[n - 1] = 3;
                } else {
                    for (int rep = 0; rep < n; rep++) {
                        color[current] = rep%2 + 1;
                        current = (current + 1)%n;
                    }
                }
            }
        }

        cout << *(max_element(color, color + n)) << endl;
        for (int i = 0; i < n; i++)
            cout << color[i] << " ";
        cout << endl;
    }
}
