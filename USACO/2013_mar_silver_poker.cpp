#include<bits/stdc++.h>
using namespace std;

int N, a, carry;
long long int answer;

int main() {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);

    cin >> N;

    carry = answer = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a;

        if (a < carry) {
            carry = a;
        } else {
            answer += (a - carry);
            carry += (a - carry);
        }
    }

    cout << answer << endl;
}
