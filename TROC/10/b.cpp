#include<bits/stdc++.h>
using namespace std;

int main() {
    int N;

    cin >> N;
    if (N == 0)
        cout << "1\n";
    if (N == 1)
        cout << "0\n";
    else {
        if (N%2 == 1)
            cout << "4";

        for (int i = 1; i <= N/2; i++)
            cout << "8";

        cout << endl;
    }
}
