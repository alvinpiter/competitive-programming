#include<bits/stdc++.h>
using namespace std;

int main() {
    double current, target;
    cin >> target;

    current = 100;
    for (int year = 1; ; year++) {
        current *= 1.01;
        current = floor(current);
        if (current >= target) {
            cout << year << endl;
            break;
        }
    }
}
