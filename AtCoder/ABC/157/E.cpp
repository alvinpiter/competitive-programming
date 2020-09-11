#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, Q;
    string S;
    set<int> pos[26];

    cin >> N >> S;

    for (int i = 0; i < N; i++)
        pos[S[i] - 'a'].insert(i);

    cin >> Q;
    for (int q = 1; q <= Q; q++) {
        int t;
        cin >> t;

        if (t == 1) {
            int idx;
            string c;

            cin >> idx >> c;
            pos[S[idx - 1] - 'a'].erase(idx - 1);
            S[idx - 1] = c[0];
            pos[S[idx - 1] - 'a'].insert(idx - 1);
        } else {
            int a, b;
            cin >> a >> b;

            int answer = 0;
            for (int c = 0; c < 26; c++) {
                auto ptr = pos[c].lower_bound(a - 1);
                if (ptr != pos[c].end() && *ptr <= b - 1)
                    answer += 1;
            }

            cout << answer << endl;
        }
    }
}
