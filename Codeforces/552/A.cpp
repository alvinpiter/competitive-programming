#include<bits/stdc++.h>
using namespace std;

int main() {
    int x[5];

    for (int i = 1; i <= 4; i++)
        cin >> x[i];

    sort(x + 1, x + 4 + 1);

    cout << x[4] - x[3] << " " << x[4] - x[2] << " " << x[4] - x[1] << endl;
}
