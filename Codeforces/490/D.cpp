#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, m, a[MAXN + 3];
long long int answer;
vector<int> posWithMod[MAXN + 3];
vector<pair<int, int> > candidate; //{idx, mod}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        posWithMod[a[i]%m].push_back(i);
    }

    answer = 0;
    for (int i = 0; i < 2 * m; i++) {
        int curMod = i % m;
        while ((int) posWithMod[curMod].size() > n/m) {
            int idx = posWithMod[curMod].back();
            posWithMod[curMod].pop_back();
            candidate.push_back({idx, curMod});
        }

        while ((int) posWithMod[curMod].size() < n/m && !candidate.empty()) {
            int idx = candidate.back().first;
            int mod = candidate.back().second;

            candidate.pop_back();

            //change mod to curMod
            int dist = (curMod >= mod ? curMod - mod : m - mod + curMod);

            answer += dist;
            a[idx] += dist;
            posWithMod[curMod].push_back(idx);
        }
    }

    cout << answer << endl;
    for (int i = 0 ; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}
