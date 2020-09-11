#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000
#define LL long long int

int N, K;
pair<int, int> loot[MAXN + 3]; //(value, mass)
multiset<int> bags;
LL answer;

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++)
        cin >> loot[i].second >> loot[i].first;

    for (int i = 0; i < K; i++) {
        int C;
        cin >> C;

        bags.insert(C);
    }

    sort(loot, loot + N);
    reverse(loot, loot + N);

    answer = 0;
    for (int i = 0; i < N; i++) {
        set<int>::iterator ptr = bags.lower_bound(loot[i].second);

        if (ptr != bags.end()) {
            answer += loot[i].first;
            bags.erase(ptr);
        }
    }

    cout << answer << endl;
}
