#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 2000000

/*
p10[i] = 10^i
p10Sum[i] = 10^0 + 10^1 + .. + 10^i
*/
LL p10[MAXN + 3], p10Sum[MAXN + 3], answer;
int N;
string s;

int main() {
    p10[0] = 1;
    p10Sum[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        p10[i] = (p10[i - 1] * 10)%MOD;
        p10Sum[i] = (p10Sum[i - 1] + p10[i])%MOD;
    }

    cin >> s;

    int N = s.length();
    for (int i = 1; i <= N; i++) {
        int digit = (s[i - 1] - '0');
        answer = (answer + (p10Sum[N - i] * digit * i)%MOD)%MOD;
    }

    cout << answer << endl;
}
