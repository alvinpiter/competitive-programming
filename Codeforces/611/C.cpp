#include<bits/stdc++.h>
using namespace std;

int n, nxt[200004];
bool hasInDegree[200003];
vector<int> origin;

int getEnd(int x) {
    while (nxt[x] != 0) {
        x = nxt[x];
    }

    return x;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nxt[i];
        hasInDegree[nxt[i]] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (hasInDegree[i] == false)
            origin.push_back(i);
    }

    if (origin.size() > 0) {
        for (int i = 0; i < origin.size(); i++) {
            int u = origin[i];
            int end = getEnd(u);

            if (i < origin.size() - 1)
                nxt[end] = origin[i + 1];
        }

        nxt[getEnd(origin.back())] = origin[0];
    }

    for (int i = 1; i <= n; i++)
        cout << nxt[i] << " ";

    cout << endl;
}
