#include<bits/stdc++.h>
using namespace std;

string S, C;
int Q, T, F;
bool reversed;
deque<char> dq;

int main() {
    cin >> S >> Q;

    for (int i = 0; i < S.length(); i++)
        dq.push_back(S[i]);

    reversed = false;
    for (int i = 1; i <= Q; i++) {
        cin >> T;

        if (T == 1)
            reversed = !reversed;
        else {
            cin >> F >> C;

            if (F == 1) {
                if (reversed)
                    dq.push_back(C[0]);
                else
                    dq.push_front(C[0]);
            } else {
                if (reversed)
                    dq.push_front(C[0]);
                else
                    dq.push_back(C[0]);
            }
        }
    }

    if (reversed) {
        for (int i = dq.size() - 1; i >= 0; i--)
            cout << dq[i];
    } else {
        for (int i = 0; i < dq.size(); i++)
            cout << dq[i];
    }

    cout << endl;
}
