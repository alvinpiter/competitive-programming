#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, answer;
    char c;

    cin >> n;

    answer = 0;
    for (int i = 1; i <= n; i++) {
        cin >> c;
        if ((c - '0')%2 == 0)
            answer += i;
    }

    cout << answer << endl;
}
