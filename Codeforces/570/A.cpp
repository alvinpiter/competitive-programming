#include<bits/stdc++.h>
using namespace std;

bool check(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num%10;
        num /= 10;
    }

    return (sum%4 == 0);
}

int main() {
    int n;
    cin >> n;

    for (int i = n; ; i++) {
        if (check(i)) {
            cout << i << endl;
            return 0;
        }
    }
}
