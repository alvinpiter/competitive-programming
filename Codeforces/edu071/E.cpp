#include<bits/stdc++.h>
using namespace std;

/*
Divide the problems into guessing the first 7 bits of x and guessing the last 7 bits of x.
To know the first 7 bits of x, guess 0000000_something
To know the last 7 bits of x, guess something_0000000
*/

int main() {
    cout << "?";
    for (int i = 1; i <= 100; i++)
        cout << " " << i;
    cout << endl;
    cout.flush();

    int response1;
    cin >> response1;

    cout << "?";
    for (int i = 1; i <= 100; i++)
        cout << " " << (i << 7);
    cout << endl;
    cout.flush();

    int response2;
    cin >> response2;

    int first7bits = ((response1 >> 7) << 7);
    int last7bits = response2 ^ ((response2 >> 7) << 7);

    cout << "! " << first7bits + last7bits << endl;
}
