#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000
#define DEBUG true

int depth[MAXN + 3], parent[MAXN + 3], capacity[MAXN + 3];
bool done[MAXN + 3];
int T, N, S, currentDepthSum;

bool checkRange(int n, int s) {
    int currentDepth = 0;
    int maxNodeAtCurrentDepth = 1;
    int numNodeAtCurrentDepth = 0;
    int minDepthSum = 0;
    int maxDepthSum = (n * n - n)/2;

    while (n > 0) {
        if (numNodeAtCurrentDepth == maxNodeAtCurrentDepth) {
            maxNodeAtCurrentDepth *= 2;
            numNodeAtCurrentDepth = 0;
            currentDepth += 1;
        }

        n -= 1;
        numNodeAtCurrentDepth += 1;
        minDepthSum += currentDepth;
    }

    if (s >= minDepthSum && s <= maxDepthSum)
        return true;
    else
        return false;
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> S;

        if (checkRange(N, S) == false) {
            cout << "NO\n";
            continue;
        }

        //Make a chain
        currentDepthSum = 0;
        for (int i = 1; i <= N; i++) {
            depth[i] = i - 1;
            parent[i] = i - 1;
            capacity[i] = (i < N ? 1 : 2);
            done[i] = false;

            currentDepthSum += depth[i];
        }

        while (currentDepthSum > S) {
            int leafWithMinDepth = -1;
            for (int i = 1; i <= N; i++) {
                if (capacity[i] == 2 && !done[i] && (leafWithMinDepth == -1 || depth[i] < depth[leafWithMinDepth])) {
                    leafWithMinDepth = i;
                }
            }

            int candidateParent = -1; //A node that is located 2 levels above leafWithMinDepth and not full
            for (int i = 1; i <= N; i++) {
                if (depth[i] == depth[leafWithMinDepth] - 2 && capacity[i] > 0) {
                    candidateParent = i;
                    break;
                }
            }

            if (candidateParent == -1) {
                done[leafWithMinDepth] = true;
                continue;
            }

            capacity[candidateParent] -= 1;

            capacity[parent[leafWithMinDepth]] += 1;
            depth[leafWithMinDepth] -= 1;
            parent[leafWithMinDepth] = candidateParent;

            currentDepthSum -= 1;
        }

        cout << "YES\n";
        for (int i = 2; i <= N; i++)
            cout << parent[i] << " ";

        cout << endl;
    }
}
