#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int t, n, k;
LL a;
bool valid;
vector<int> bitPos;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        bitPos.clear();
        valid = true;
        for (int i = 1; i <= n; i++) {
            cin >> a;

            int pos = 0;
            while (a > 0) {
                int rem = a%k;
                if (rem > 1)
                    valid = false;

                if (rem > 0)
                    bitPos.push_back(pos);

                a /= k;
                pos += 1;
            }
        }

        sort(bitPos.begin(), bitPos.end());
        for (int i = 1; i < bitPos.size(); i++) {
            if (bitPos[i] == bitPos[i - 1])
                valid = false;
        }

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
