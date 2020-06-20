#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, seq[MAXN + 3], posMini[MAXN + 3], posMaxi[MAXN + 3];
vector<int> brackets;
set<int> posEmpty;

int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        posMini[i] = MAXN;
        posMaxi[i] = -MAXN;
    }

    for (int i = 1; i <= N; i++) {
        cin >> seq[i];

        posMini[seq[i]] = min(posMini[seq[i]], i);
        posMaxi[seq[i]] = max(posMaxi[seq[i]], i);

        if (seq[i] == 0)
            posEmpty.insert(i);
    }

    //check if there is an empty cell between two cell with same color
    for (int i = 1; i <= N; i++) {
        if (posMini[i] < posMaxi[i]) {
            auto ptr = posEmpty.lower_bound(posMini[i]);
            if (ptr != posEmpty.end() && *ptr < posMaxi[i]) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (seq[i] > 0) {
            if (i == posMini[seq[i]])
                brackets.push_back(seq[i]);

            if (i == posMaxi[seq[i]])
                brackets.push_back(-seq[i]);

            if (i > posMini[seq[i]] && i < posMaxi[seq[i]]) {
                brackets.push_back(-seq[i]);
                brackets.push_back(seq[i]);
            }
        }
    }

    //bracket matching
    int answer = 0;
    stack<int> st;

    for (int i = 0; i < brackets.size(); i++) {
        if (brackets[i] > 0)
            st.push(brackets[i]);
        else {
            if (st.top() + brackets[i] != 0) {
                cout << -1 << endl;
                return 0;
            } else {
                st.pop();
            }
        }

        answer = max(answer, (int) st.size());
    }

    cout << answer << endl;
}
