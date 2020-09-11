#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL A, B, N;

    cin >> A >> B >> N;

    LL mul = (B <= N ? B - 1 : N);

    cout << (A * mul)/B << endl;
}
