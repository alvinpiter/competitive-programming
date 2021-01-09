#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 500000
#define SQRT 750

int N, Q, C[MAXN + 3];
int ctr[MAXN + 3], cntUniq, answer[MAXN + 3];
vector<pair<pair<int, int>, int> > queries;

void add(int num) {
    if (ctr[num] == 0) {
        cntUniq += 1;
    }

    ctr[num] += 1;
}

void remove(int num) {
    if (ctr[num] == 1) {
        cntUniq -= 1;
    }

    ctr[num] -= 1;
}

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first.first/SQRT == b.first.first/SQRT) {
        return a.first.second < b.first.second;
    } else {
        return a.first.first < b.first.first;
    }
}


int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }

    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        queries.push_back(make_pair(make_pair(l, r), i));
    }

    sort(queries.begin(), queries.end(), comp);

    memset(ctr, 0, sizeof(ctr));
    cntUniq = 0;

    int l = 1, r = 0;
    for (int i = 0; i < Q; i++) {
        int targetL = queries[i].first.first;
        int targetR = queries[i].first.second;

        while (r < targetR) {
            add(C[r + 1]);
            r++;
        }

        while (r > targetR) {
            remove(C[r]);
            r--;
        }

        while (l < targetL) {
            remove(C[l]);
            l++;
        }

        while (l > targetL) {
            add(C[l - 1]);
            l--;
        }

        answer[queries[i].second] = cntUniq;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", answer[i]);
    }

}
