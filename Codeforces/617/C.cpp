#include<bits/stdc++.h>
using namespace std;

int T, N;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        int bestL = -1, bestR = -1;
        int currentX = 0;
        int currentY = 0;
        map<pair<int, int>, int> pos;

        pos[make_pair(currentX, currentY)] = 0;
        for (int i = 1; i <= N; i++) {
            char C;
            cin >> C;

            switch (C) {
                case 'L':
                    currentX -= 1;
                    break;
                case 'R':
                    currentX += 1;
                    break;
                case 'U':
                    currentY += 1;
                    break;
                case 'D':
                    currentY -= 1;
                    break;
            }

            pair<int, int> current = make_pair(currentX, currentY);

            if (pos.find(current) != pos.end()) {
                int prev = pos[current];
                if (bestL == -1 || i - prev < bestR - bestL) {
                    bestL = prev + 1;
                    bestR = i;
                }
            }

            pos[current] = i;
        }

        if (bestL == -1)
            cout << "-1\n";
        else
            cout << bestL << " " << bestR << endl;
    }
}
