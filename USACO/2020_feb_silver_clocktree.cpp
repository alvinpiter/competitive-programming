#include<bits/stdc++.h>
using namespace std;
#define MAXN 2500

/*
Let's pick a starting vertex S and split the vertices into two set:
* oddSet -> set of vertices whose distance from S is odd
* evenSet -> set of vertices whose distance from S is even

Let's define a quantity Q as:
Q = (sum(clock(x) for x in oddSet) - sum(clock(x) for x in evenSet)) % 12

Initially, the value of Q is Q0. We claim that at any time, the value of Q is
either Q0 or Q0 + 1.
Proof:
Divide into two cases:
* We move even number of steps. We will visit the same number of even and odd vertex, so Q
does not change.
* We move odd number of steps. We will visit 1 more odd vertex than even vertex, so Q will increase
by 1.

In the final state, the value of Q is 0, hence the value of Q0 must be either 0 or 11.

Now we claim that if Q0 is 0, then we can construct a solution:
Imagine we start from vertex a, and there is a vertex b that only has 1 neighbor.
We will repeat path a-b like a-b-a-b..-a until clock at b is 12 and then removed it from the tree.
We are left with the same problem (because a-b-a path is even in length, so Q does not change) but with 1 less vertex.
Just repeat this procedure.

If Q0 is 11, we just move to its neighbor, then start from it. Q0 will be 0 in the neighbor.
*/

int N, clok[MAXN + 3], sumOdd, sumEven, answer;
vector<int> adj[MAXN + 3];

int mod12(int num) {
    if (num >= 0)
        return num%12;
    else
        return (abs(num)/12 + (abs(num)%12 == 0 ? 0 : 1))*12 + num;
}

void DFS(int u, int prv, int depth) {
    if (depth%2 == 0)
        sumEven += clok[u];
    else
        sumOdd += clok[u];

    for (auto v: adj[u]) {
        if (v != prv) {
            DFS(v, u, depth + 1);
        }
    }
}

int main() {
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> clok[i];

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /*
        Brute force starting position.
        This can be simplified, because if it is possible to do so from node i, then
        it is possible to do so from all node with even distance from i.
    */
    answer = 0;
    for (int s = 1; s <= N; s++) {
        sumOdd = sumEven = 0;
        DFS(s, s, 0);

        int Q = mod12(sumOdd - sumEven);
        if (Q == 0 || Q == 11)
            answer += 1;
    }

    cout << answer << endl;
}
