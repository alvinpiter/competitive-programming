#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, K, numRemoved[MAXN + 3], numCover[MAXN + 3];
pair<int, int> segments[MAXN + 3];
vector<int> events[MAXN + 3];
vector<int> removedSegments;
set<pair<int, int> > activeSegments;

int main() {
    cin >> N >> K;

    for (int i = 1; i <= N; i++) {
        int l, r;
        cin >> l >> r;

        segments[i] = {l, r};

        events[l].push_back(i);
        events[r + 1].push_back(-i);

        numCover[l] += 1;
        numCover[r + 1] -= 1;
    }

    memset(numRemoved, 0, sizeof(numRemoved));
    for (int i = 1; i <= MAXN; i++) {
        numCover[i] += numCover[i - 1];
        numRemoved[i] += numRemoved[i - 1];

        for (auto idx: events[i]) {
            if (idx > 0) {
                activeSegments.insert({segments[idx].second, idx});
            } else {
                set<pair<int, int> >::iterator ptr = activeSegments.find({segments[-idx].second, -idx});
                if (ptr != activeSegments.end())
                    activeSegments.erase(ptr);
            }
        }

        int countToBeRemoved = (numCover[i] - numRemoved[i]) - K;

        while (countToBeRemoved > 0) {
            pair<int, int> toBeRemoved = *(--activeSegments.end());

            //Update answer
            removedSegments.push_back(toBeRemoved.second);

            //Update prefix sum
            numRemoved[i] += 1;
            numRemoved[toBeRemoved.first + 1] -= 1;

            //Remove from active segments
            activeSegments.erase(activeSegments.find(toBeRemoved));

            countToBeRemoved -= 1;
        }
    }

    cout << removedSegments.size() << endl;
    for (auto id: removedSegments)
        cout << id << " ";

    cout << endl;
}
