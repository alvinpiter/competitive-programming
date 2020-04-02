#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define DEBUG false

int T, N, p[MAXN + 3], c[MAXN + 3], numCycles;
bool visited[MAXN + 3];
vector<int> cycles[MAXN + 3];

void generateCycles() {
    //reset cycles from previous test case
    for (int i = 0; i < numCycles; i++) cycles[i].clear();
    numCycles = 0;

    for (int i = 0; i < N; i++)
        visited[i] = false;

    numCycles = 0;
    for (int i = 0; i < N; i++) {
        if (visited[i] == false) {
            int current = i;
            while (visited[current] == false) {
                visited[current] = true;
                cycles[numCycles].push_back(current);

                current = p[current];
            }

            numCycles += 1;
        }
    }
}

/*
Can we make smaller cycle from cycle with index cycleIndex such that one of the cycle has nodes with the same color
We make smaller cycle by hopping hopSize nodes at a time
hopSize must be divisor of cycle length
*/
bool check(int cycleIndex, int hopSize) {
    int cycleLen = (int) cycles[cycleIndex].size();
    for (int i = 0; i < hopSize; i++) {
        bool allSameColor = true;

        for (int rep = 0, current = i; rep < cycleLen/hopSize; rep++, current = (current + hopSize)%cycleLen) {
            if (c[cycles[cycleIndex][current]] != c[cycles[cycleIndex][i]])
                allSameColor = false;
        }

        if (allSameColor)
            return true;
    }

    return false;
}

int main() {
    scanf("%d", &T);

    numCycles = 0;
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &p[i]);
            p[i] -= 1;
        }

        for (int i = 0; i < N; i++)
            scanf("%d", &c[i]);

        generateCycles();

        int answer = N;
        for (int cycleIndex = 0; cycleIndex < numCycles; cycleIndex++) {
            int len = (int) cycles[cycleIndex].size();

            for (int div = 1; div * div <= len; div++) {
                if (len % div == 0) {
                    if (check(cycleIndex, div))
                        answer = min(answer, div);

                    if (check(cycleIndex, len/div))
                        answer = min(answer, len/div);
                }
            }
        }

        printf("%d\n", answer);
    }
}
