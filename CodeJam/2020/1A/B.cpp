#include<bits/stdc++.h>
using namespace std;
#define MAXLG 30

int main() {
    int T, N;
    int p2[MAXLG + 3];

    p2[0] = 1;
    for (int i = 1; i <= MAXLG; i++)
        p2[i] = 2 * p2[i - 1];

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        cout << "Case #" << cases << ":\n";

        if (N <= 35) {
            for (int i = 1; i <= N; i++)
                cout << i << " " << 1 << endl;

            continue;
        }

        int tempN = N - MAXLG;
        int sum = 0;
        int depth = 1;

        int msb;
        for (msb = 30; msb >= 0; msb--) {
            if (tempN & (1 << msb))
                break;
        }

        bool isInFirstColumn = true;
        for (int lg = 0; lg <= msb; lg++) {
            if (tempN & (1 << lg)) {
                if (isInFirstColumn) {
                    for (int j = 1; j <= depth; j++)
                        cout << depth << " " << j << endl;

                    isInFirstColumn = false;
                } else {
                    for (int j = depth; j >= 1; j--)
                        cout << depth << " " << j << endl;

                    isInFirstColumn = true;
                }

                sum += p2[depth - 1];
            } else {
                cout << depth << " " << (isInFirstColumn ? 1 : depth) << endl;
                sum += 1;
            }

            depth += 1;
        }

        int diff = N - sum;

        while (diff > 0) {
            diff -= 1;
            sum += 1;

            cout << depth << " " << (isInFirstColumn ? 1 : depth) << endl;

            depth += 1;
        }
    }
}
