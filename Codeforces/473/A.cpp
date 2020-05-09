#include<bits/stdc++.h>
using namespace std;

/*
If n is even, Mahmoud can take it all.
If n is odd, the next number for Ehab must be odd, so Ehab can take it all.
*/

int main() {
    int n;
    cin >> n;

    if (n%2 == 0)
        cout << "Mahmoud\n";
    else
        cout << "Ehab\n";
}
