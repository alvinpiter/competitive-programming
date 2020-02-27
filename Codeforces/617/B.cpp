
#include<bits/stdc++.h>
using namespace std;

int T, money, total;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> money;

        total = 0;
        while (money > 0) {
            int spend = (money < 10 ? money : (money/10)*10);
            int cashback = spend/10;

            money = money - spend + cashback;
            total += spend;
        }

        cout << total << endl;
    }
}
