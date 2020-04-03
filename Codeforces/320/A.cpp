#include<bits/stdc++.h>
using namespace std;

int main() {
    int x, answer;
    cin >> x;

    answer = 0;
    while (x > 0) {
        answer += x%2;
        x /= 2;
    }

    cout << answer << endl;
}
