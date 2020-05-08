#include<bits/stdc++.h>
using namespace std;

int N, number;
vector<int> st;
bool leftOverParitySame;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> number;
        if (!st.empty() && st.back() == number%2)
            st.pop_back();
        else
            st.push_back(number%2);
    }

    leftOverParitySame = true;
    for (int i = 0; i < st.size(); i++) {
        if (st[i] != st[0])
            leftOverParitySame = false;
    }

    if (leftOverParitySame)
        cout << "YES\n";
    else
        cout << "NO\n";
}
