#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL N, M, answer;

int main() {
    cin >> N >> M;

    answer = 0;
    answer += 2 * ((M - 2) * 2 + (M - 2) * 2 + (M - 3) * (M - 2));
    answer += 2 * ((N - 2) * 2 + (N - 2) * 2 + (N - 3) * (N - 2));

    cout << answer << endl;
}
