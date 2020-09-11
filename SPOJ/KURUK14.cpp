#include<bits/stdc++.h>
using namespace std;

/*
Type-i is a number which have i - 1 numbers to the left of it or N - x numbers to the right of it
*/
int getType(int N, int x) {
    if (x < (N + 1)/2)
        return x + 1;
    else
        return N - x;
}

int main() {
    int T, N, counter[1003];

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        memset(counter, 0, sizeof(counter));
        for (int i = 1; i <= N; i++) {
            int a;
            cin >> a;

            counter[getType(N, a)] += 1;
        }

        bool valid = true;
        for (int i = 1; i <= N/2; i++) {
            if (counter[i] > 2)
                valid = false;
        }

        if (N%2 == 1 && counter[(N + 1)/2] != 1)
            valid = false;

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
