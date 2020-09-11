#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[100003], countOdd = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i]%2 == 0)
            countOdd += 1;
    }

    if (countOdd != 0 && countOdd != n)
        sort(a, a + n);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}
