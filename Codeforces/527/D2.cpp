#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, h[MAXN + 3], maxi;

int main() {
    cin >> N;

    maxi = 0;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
        maxi = max(maxi, h[i]);
    }

    h[0] = maxi;
    h[N + 1] = maxi;

    stack<int> st;
    int lastMatch = 0;
    bool valid = true;
    for (int i = 1; i <= N + 1; i++) {
        if (h[i] == maxi) {
            if (!st.empty())
                valid = false;

            //empty stack
            while (!st.empty()) st.pop();
            lastMatch = 0;
        } else {
            if (!st.empty() && h[st.top()] == h[i]) {
                if (st.top() == i - 1) {
                    st.pop();
                    lastMatch = h[i];
                } else {
                    if (h[i] >= lastMatch) {
                        st.pop();
                        lastMatch = h[i];
                    } else {
                        st.push(i);
                    }
                }
            } else {
                st.push(i);
            }
        }
    }

    if (valid)
        cout << "YES\n";
    else
        cout << "NO\n";
}

/*
Corner cases:

6
3 1 2 2 1 3

8
3 2 1 1 2 1 1 3
*/
