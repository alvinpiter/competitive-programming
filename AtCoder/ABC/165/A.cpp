#include<bits/stdc++.h>
using namespace std;

int main() {
    int K, A, B;

    cin >> K >> A >> B;

    int l = A/K + (A%K == 0 ? 0 : 1);
    int r = B/K;

    if (l > r)
        cout << "NG\n";
    else
        cout << "OK\n";
}
