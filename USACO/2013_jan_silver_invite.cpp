#include<bits/stdc++.h>
using namespace std;
#define MAXN 250000

/*
group[i] -> cows which is in group i
groupsOf[i] -> groups which contains cow i
cntInvited[i] -> how many cows in group i is already invited
isInvited[i] -> is cow i invited to the party
*/

vector<int> group[MAXN + 3], groupsOf[MAXN + 3];
int N, G, cntInvited[MAXN + 3];
bool isInvited[MAXN + 3];

int main() {
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);

    cin >> N >> G;
    for (int i = 1; i <= G; i++) {
        int cnt;
        cin >> cnt;

        for (int j = 1; j <= cnt; j++) {
            int id;
            cin >> id;

            group[i].push_back(id);
            groupsOf[id].push_back(i);
        }
    }

    memset(cntInvited, 0, sizeof(cntInvited));

    queue<int> groupsToBeProcessed;

    isInvited[1] = true;
    for (auto g: groupsOf[1]) {
        cntInvited[g] += 1;
        if (cntInvited[g] == group[g].size() - 1) {
            groupsToBeProcessed.push(g);
        }
    }

    while (!groupsToBeProcessed.empty()) {
        int g = groupsToBeProcessed.front(); groupsToBeProcessed.pop();
        for (auto m: group[g]) {
            if (!isInvited[m]) {
                isInvited[m] = true;
                for (int gm: groupsOf[m]) {
                    cntInvited[gm] += 1;
                    if (cntInvited[gm] == group[gm].size() - 1)
                        groupsToBeProcessed.push(gm);
                }
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        if (isInvited[i])
            answer += 1;
    }

    cout << answer << endl;
}
