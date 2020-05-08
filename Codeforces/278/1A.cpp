#include<bits/stdc++.h>
using namespace std;

/*
Buy at most 200 ATK and 100 DEF.
*/

int main() {
    int hpY, atkY, defY, hpM, atkM, defM, hpPrice, atkPrice, defPrice;

    cin >> hpY >> atkY >> defY;
    cin >> hpM >> atkM >> defM;
    cin >> hpPrice >> atkPrice >> defPrice;

    int miniCost = 1e9;
    for (int cntAtk = 0; cntAtk <= 200; cntAtk++) {
        for (int cntDef = 0; cntDef <= 100; cntDef++) {
            if (atkY + cntAtk <= defM)
                continue;

            int numRounds = hpM/(atkY + cntAtk - defM) + (hpM%(atkY + cntAtk - defM) == 0 ? 0 : 1);
            int hpLeft = hpY - numRounds * max(0, atkM - defY - cntDef);

            int cost = cntAtk * atkPrice + cntDef * defPrice + (hpLeft <= 0 ? (abs(hpLeft) + 1)*hpPrice : 0);
            miniCost = min(miniCost, cost);
        }
    }

    cout << miniCost << endl;
}
