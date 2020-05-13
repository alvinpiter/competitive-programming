#include<bits/stdc++.h>
using namespace std;

int main() {
    int A, B, C, K, sum;

    cin >> A >> B >> C >> K;

    int take;

    sum = 0;

    take = min(A, K);
    sum += take;
    K -= take;

    take = min(B, K);
    sum += 0;
    K -= take;

    take = min(C, K);
    sum -= take;
    K -= take;

    cout << sum << endl;
}
