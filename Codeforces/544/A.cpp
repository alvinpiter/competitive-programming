#include<bits/stdc++.h>
using namespace std;

int h1, m1, h2, m2, t1, t2, middle;

int main() {
    scanf("%d:%d", &h1, &m1);
    scanf("%d:%d", &h2, &m2);

    t1 = 60 * h1 + m1;
    t2 = 60 * h2 + m2;

    middle = (t1 + t2)/2;

    int h = middle/60;
    int m = middle - (middle/60)*60;

    if (h < 10)
        cout << "0" << h;
    else
        cout << h;

    cout << ":";

    if (m < 10)
        cout << "0" << m;
    else
        cout << m;

    cout << endl;
}
