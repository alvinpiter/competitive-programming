#include<bits/stdc++.h>
using namespace std;

int N, A[10], X;

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    cin >> X;
    for (int i = 1; i <= N; i++) {
        if (A[i] == X) {
            cout << i << endl;
            return 0;
        }
    }
}
