#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i + j)%2 == 0)
                cout << "B";
            else
                cout << "W";
        }
        cout << endl;
    }
}
