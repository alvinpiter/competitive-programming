#include<bits/stdc++.h>
using namespace std;

int T, A, B, C;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> A >> B >> C;

        int minCost = 1e9, solA, solB, solC;
        for (int b = 1; b <= 20000; b++) {
            int costB = abs(B - b);

            int costA = 1e9;
            int bestA;
            for (int a = 1; a * a <= b; a++) {
                if (b % a == 0) {
                    if (abs(A - a) < costA) {
                        costA = abs(A - a);
                        bestA = a;
                    }

                    if (abs(A - b/a) < costA) {
                        costA = abs(A - b/a);
                        bestA = b/a;
                    }
                }
            }

            int costC = 1e9;
            int bestC;
            if (C < b) {
                costC = b - C;
                bestC = b;
            } else {
                if (abs((C/b) * b - C) < abs((C/b + 1) * b - C)) {
                    costC = abs((C/b) * b - C);
                    bestC = (C/b) * b;
                } else {
                    costC = abs((C/b + 1) * b - C);
                    bestC = (C/b + 1) * b;
                }
            }

            int cost = costA + costB + costC;
            if (cost < minCost) {
                minCost = cost;
                solA = bestA;
                solB = b;
                solC = bestC;
            }
        }

        cout << minCost << endl;
        cout << solA << " " << solB << " " << solC << endl;
    }
}
