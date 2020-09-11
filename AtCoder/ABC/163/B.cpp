#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, M, tot;

    cin >> N >> M;

    tot = 0;
    for (int i = 1; i <= M; i++) {
        int A;
        cin >> A;

        tot += A;
    }

    if (tot > N)
        cout << -1 << endl;
    else
        cout << N - tot << endl;
}
