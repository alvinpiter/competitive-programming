#include<bits/stdc++.h>
using namespace std;

/*
If i-th bit of m is on, we have an option to turn it off and then turn on all the bits j (j < i)
If i-th bit of m is off, nothing we can do

We can also use x = m.
*/

int main() {
    int n, a[100003], prefix[100003];
    string s;

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cin >> s;

    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + a[i];

    int best = 0;
    int sum = 0;
    for (int i = n; i >= 1; i--) {
        if (s[i - 1] == '0')
            continue;

        if (s[i - 1] == '1') {
            best = max(best, sum + prefix[i - 1]);
            sum += a[i];
        }
    }

    best = max(best, sum);

    cout << best << endl;
}
