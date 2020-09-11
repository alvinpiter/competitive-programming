#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
First let's find a way to calculate f(l, r).
Convert every element in array a such that if l <= ai <= r, convert it to 1 and otherwise to 0. Also set a0 = 0.
Number of connected component is therefore equal to number of adjacent elements with value 0 and 1.

Now we will use contribution technique. Imagine two adjacent value ai and aj. There are 3 cases:
* ai = aj. These adjacent elements will never contribute to the answer
* ai < aj. These adjacent elements will contribute to the answer if ai + 1 <= l <= aj and r >= aj.
* ai > aj. These adjacent elements will contribute to the answer if l <= aj and aj <= r < ai.
*/

int main() {
    int n, a[100003];

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    a[0] = 0;

    LL answer = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == a[i + 1])
            continue;

        LL temp;
        if (a[i] < a[i + 1]) {
            int cntL = a[i + 1] - (a[i] + 1) + 1;
            int cntR = n - a[i + 1] + 1;

            temp = (LL) cntL * cntR;
        } else {
            int cntL = a[i + 1];
            int cntR = a[i] - a[i + 1];

            temp = (LL) cntL * cntR;
        }

        answer += temp;
    }

    cout << answer << endl;
}
