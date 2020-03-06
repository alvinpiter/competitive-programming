#include<bits/stdc++.h>
using namespace std;

int n, e, d, answer;

int main() {
    cin >> n >> d >> e;

    answer = 1e9;
    for (int dollar = 0; dollar * d <= n; dollar++) {
        int rem = n - dollar * d;
        int euro = rem/e - (rem/e)%5;

        answer = min(answer, rem - euro * e);
    }

    cout << answer << endl;
}
