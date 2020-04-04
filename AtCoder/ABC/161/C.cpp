#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL N, K;

    cin >> N >> K;

    N %= K;
    cout << min(N, K - N) << endl;
}
