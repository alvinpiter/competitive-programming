#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
For each index j, define left[j] as smallest index i such that there are at most K
other id other than id[j]. Assume we already know the value of left[j - 1] and we want to
calculate left[j]. There are two cases to consider:
* id[j] = id[j - 1]. Then left[j] = left[j - 1]
* id[j] != id[j - 1]. Let's prove left[j] >= left[j - 1] by contradiction.
  Let's say left[j] < left[j - 1]. That means that there are at most K id different with
  id[j] between left[j] and j - 1. That also means that there are at most K id different with
  id[j - 1] between left[j] and j - 1. We see that left[j - 1] is not minimal. Hence, contradiction.

In all cases left[j] >= left[j - 1], so this problem can be solved with sliding window algorithm.
We will maintain the number of occurence of each id in the window.
*/

int N, K, id[MAXN + 3], cntUniq, answer;
map<int, int> cnt;

void add(int i) {
    cnt[i] += 1;
    if (cnt[i] == 1)
        cntUniq += 1;
}

void remove(int i) {
    cnt[i] -= 1;
    if (cnt[i] == 0)
        cntUniq -= 1;
}

int main() {
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> id[i];

    int ptr = 1;

    cntUniq = 0;
    for (int i = 1; i <= N; i++) {
        add(id[i]);
        while (cntUniq > K + 1) {
            remove(id[ptr]);
            ptr += 1;
        }

        answer = max(answer, cnt[id[i]]);
    }

    cout << answer << endl;
}
