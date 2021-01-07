#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 200000

/*
Merge small group to large group. The overall complexity will be O(N log N).

Assume f(x) = maximum number of merge for group with size x.
f(x) = max(f(x - k) + f(k) + min(x - k, k))

*/

int N, Q, parent[MAXN + 3], sz[MAXN + 3];
map<int, map<int, int> > classCounter; //classCounter[i] -> counter for group whose leader is i

int findSet(int i) {
    return (i == parent[i] ? i : parent[i] = findSet(parent[i]));
}

bool isSameSet(int i, int j) {
    return (findSet(i) == findSet(j));
}

void merge(int a, int b) {
    if (isSameSet(a, b)) {
        return;
    }

    int pa = findSet(a);
    int pb = findSet(b);

    if (sz[pa] <= sz[pb]) {
        //merge pa to pb
        for (auto ptr = classCounter[pa].begin(); ptr != classCounter[pa].end(); ++ptr) {
            int klas = ptr->first;
            int ctr = ptr->second;

            if (classCounter[pb].find(klas) == classCounter[pb].end()) {
                classCounter[pb][klas] = ctr;
            } else {
                classCounter[pb][klas] += ctr;
            }
        }

        parent[pa] = pb;
        sz[pb] += sz[pa];
    } else {
        //merge pb to pa
        for (auto ptr = classCounter[pb].begin(); ptr != classCounter[pb].end(); ++ptr) {
            int klas = ptr->first;
            int ctr = ptr->second;

            if (classCounter[pa].find(klas) == classCounter[pa].end()) {
                classCounter[pa][klas] = ctr;
            } else {
                classCounter[pa][klas] += ctr;
            }
        }

        parent[pb] = pa;
        sz[pa] += sz[pb];
    }
}

int query(int a, int b) {
    int leader = findSet(a);
    return classCounter[leader][b];
}

int main() {
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;

        int klas;
        scanf("%d", &klas);

        map<int, int> ctr;
        ctr[klas] = 1;

        classCounter[i] = ctr;
    }

    for (int i = 1; i <= Q; i++) {
        int t, a, b;

        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) {
            merge(a, b);
        } else {
            printf("%d\n", query(a, b));
        }
    }
}
