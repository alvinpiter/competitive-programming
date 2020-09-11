#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int t, n, color[MAXN + 3];
    char s[MAXN + 3];
    vector<int> temp;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        scanf("%s", s);

        bool anySolution = false;

        for (int threshold = 0; threshold <= 10; threshold++) {
            int leftMostColor2 = n;
            int rightMostColor1 = -1;

            for (int i = 0; i < n; i++)
                color[i] = -1;

            for (int i = 0; i < n; i++) {
                int currentDigit = s[i] - '0';
                if (currentDigit < threshold) {
                    color[i] = 1;
                    rightMostColor1 = max(i, rightMostColor1);
                }

                if (currentDigit > threshold) {
                    color[i] = 2;
                    leftMostColor2 = min(i, leftMostColor2);
                }
            }

            for (int i = 0; i < n; i++) {
                int currentDigit = s[i] - '0';
                if (currentDigit == threshold) {
                    if (i < leftMostColor2) {
                        color[i] = 2;
                    } else if (i > rightMostColor1) {
                        color[i] = 1;
                    }
                }
            }

            temp.clear();
            for (int i = 0; i < n; i++) {
                if (color[i] == 1)
                    temp.push_back(s[i] - '0');
            }

            for (int i = 0; i < n; i++) {
                if (color[i] == 2)
                    temp.push_back(s[i] - '0');
            }

            bool valid = true;
            if (temp.size() != n) valid = false;
            for (int i = 1; i < temp.size(); i++) {
                if (temp[i] < temp[i - 1])
                    valid = false;
            }

            if (valid) {
                anySolution = true;
                for (int i = 0; i < n; i++)
                    printf("%d", color[i]);
                printf("\n");

                break;
            }
        }

        if (!anySolution) {
            printf("-\n");
        }
    }
}
