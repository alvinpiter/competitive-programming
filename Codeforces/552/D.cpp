#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, batt, accu, accuCapacity;

    scanf("%d%d%d", &n, &batt, &accu);

    accuCapacity = accu;

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int s;
        scanf("%d", &s);

        if (s == 0) {
            //prioritize accu
            if (accu > 0) {
                accu -= 1;
            } else if (batt > 0) {
                batt -= 1;
            } else {
                break;
            }
        } else {
            //If accu is full, use accu. Otherwise prioritize batt.

            if (accu == accuCapacity) {
                accu -= 1;
            } else {
                if (batt > 0) {
                    batt -= 1;
                    accu = min(accu + 1, accuCapacity);
                } else if (accu > 0) {
                    accu -= 1;
                } else {
                    break;
                }
            }
        }

        answer = i;
    }

    printf("%d\n", answer);
}
