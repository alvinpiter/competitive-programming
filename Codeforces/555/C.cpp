#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, a[MAXN + 3], fromLeft[MAXN + 3], fromRight[MAXN + 3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    fromLeft[1] = 1;
    for (int i = 2; i <= n; i++) {
        fromLeft[i] = (a[i] < a[i - 1] ? fromLeft[i - 1] + 1 : 1);
    }

    fromRight[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        fromRight[i] = (a[i] < a[i + 1] ? fromRight[i + 1] + 1 : 1);
    }

    int l = 1, r = n, lastNumberTaken = -1;
    string answer = "";

    while (l <= r) {
        if (a[l] < a[r]) {
            if (lastNumberTaken < a[l]) {
                answer += "L";
                lastNumberTaken = a[l];
                l += 1;
            } else if (lastNumberTaken < a[r]) {
                answer += "R";
                lastNumberTaken = a[r];
                r -= 1;
            } else
                break;
        } else if (a[l] > a[r]) {
            if (lastNumberTaken < a[r]) {
                answer += "R";
                lastNumberTaken = a[r];
                r -= 1;
            } else if (lastNumberTaken < a[l]) {
                answer += "L";
                lastNumberTaken = a[l];
                l += 1;
            } else
                break;
        } else if (a[l] == a[r]) {
            if (lastNumberTaken < a[l]) {
                if (fromRight[l] > fromLeft[r]) {
                    for (int i = 1; i <= fromRight[l]; i++)
                        answer += "L";
                } else {
                    for (int i = 1; i <= fromLeft[r]; i++)
                        answer += "R";
                }
            }

            break;
        }
    }

    cout << answer.length() << endl;
    cout << answer << endl;
}
