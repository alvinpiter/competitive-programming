#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e18
#define MAXN 100000

/*
numLeaves[u] = how many leaves in subtree u
sumDist[u] = sum of distance from u to all leaves below it

Re-rooting technique. Suppose currently we are at folder u and current cost is currentCost
and we want to go to folder v. Here is how the currentCost would change:
* Add '../' (3 characters) to all files not not on subtree v.
* Distance to all files in subtree v will decrease by the length of folder v.

Nice problem.
*/

int N, numLeaves[MAXN + 3];
LL sumDist[MAXN + 3], answer;
vector<pair<int, int> > children[MAXN + 3]; //{child, edge weight}

//Read input and build tree
void buildTree() {
    string name[MAXN + 3];
    vector<int> childIds[MAXN + 3];

    for (int i = 1; i <= N; i++) {
        cin >> name[i];

        int childCount;
        cin >> childCount;
        for (int j = 1; j <= childCount; j++) {
            int childId;
            cin >> childId;

            childIds[i].push_back(childId);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (auto childId: childIds[i]) {
            bool isFile = childIds[childId].empty();
            if (isFile) {
                //append just file name, example: file1
                children[i].push_back({childId, name[childId].length()});
            } else {
                //append folder name and a slash, example: folder1/
                children[i].push_back({childId, name[childId].length() + 1});
            }
        }
    }
}

void DFS1(int u, int prv) {
    numLeaves[u] = (children[u].empty() ? 1 : 0);
    sumDist[u] = 0;
    for (auto e: children[u]) {
        int v = e.first;
        int cost = e.second;

        if (v != prv) {
            DFS1(v, u);
            numLeaves[u] += numLeaves[v];
            sumDist[u] += sumDist[v] + (LL) cost * numLeaves[v];
        }
    }
}

void DFS2(int u, int prv, LL currentSumDist) {
    if (!children[u].empty())
        answer = min(answer, currentSumDist);

    for (auto e: children[u]) {
        int v = e.first;
        int cost = e.second;

        if (v != prv) {
            LL newSumDist = currentSumDist + 3 * (numLeaves[1] - numLeaves[v]) - (cost * numLeaves[v]);
            DFS2(v, u, newSumDist);
        }
    }
}

int main() {
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);

    cin >> N;

    buildTree();

    DFS1(1, 0);

    answer = INF;
    DFS2(1, 0, sumDist[1]);

    cout << answer << endl;
}
