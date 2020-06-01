#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000000000000000

int main() {
    int N;
    LL a, result;
    bool exceed, zeroExist;

    cin >> N;

    result = 1;
    exceed = false;
    zeroExist = false;
    for (int i = 1; i <= N; i++) {
        cin >> a;

        if (a == 0) {
            zeroExist = true;
            break;
        }

        if (a > INF/result) {
            exceed = true;
            continue;
        } else
            result *= a;
    }

    if (zeroExist)
        cout << 0 << endl;
    else if (exceed)
        cout << -1 << endl;
    else
        cout << result << endl;
}
