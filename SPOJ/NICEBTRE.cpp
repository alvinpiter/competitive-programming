#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000

int T;
string S;

pair<int, int> buildTree(int idx, int depth) {
    if (S[idx] == 'l')
        return make_pair(idx, depth);
    else {
        pair<int, int> resultLeft = buildTree(idx + 1, depth + 1);
        pair<int, int> resultRight = buildTree(resultLeft.first + 1, depth + 1);

        return make_pair(resultRight.first, max(resultLeft.second, resultRight.second));
    }
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> S;

        pair<int, int> result = buildTree(0, 0);

        cout << result.second << endl;
    }
}
