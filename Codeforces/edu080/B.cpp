#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int T, A, B;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> A >> B;

        int tenB = 1; //10^b
        int countB = 0;
        for (int lenB = 1; lenB <= 9; lenB++) {
            tenB *= 10;

            if (tenB - 1 <= B)
                countB += 1;
            else
                break;
        }

        cout << (LL) A * countB << endl;
    }
}
