#include<bits/stdc++.h>
using namespace std;

int T, N;
vector<string> opponents;

char getBetterHand(char c) {
    if (c == 'P') return 'S';
    if (c == 'R') return 'P';
    if (c == 'S') return 'R';
}

pair<bool, string> solve(vector<int>& candidate, int round) {
    set<char> uniq;
    for (auto id: candidate) {
        char hand = opponents[id][round% (int) opponents[id].length()];
        uniq.insert(hand);
    }

    if ((int) uniq.size() == 1) {
        char myHand = getBetterHand(*uniq.begin());
        return {true, string(1, myHand)};
    }

    if ((int) uniq.size() == 2) {
        char firstHand = *uniq.begin();
        char secondHand = *uniq.rbegin();
        char myHand = getBetterHand(firstHand) == secondHand ? secondHand : firstHand;

        vector<int> nextCandidate;
        for (auto id: candidate) {
            char hand = opponents[id][round% (int) opponents[id].length()];
            if (hand == myHand)
                nextCandidate.push_back(id);
        }

        auto result = solve(nextCandidate, round + 1);
        if (result.first == false)
            return {false, "IMPOSSIBLE"};
        else
            return {true, string(1, myHand) + result.second};
    }

    if ((int) uniq.size() == 3) {
        return {false, "IMPOSSIBLE"};
    }
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        opponents.clear();
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;

            opponents.push_back(s);
        }

        vector<int> candidate;
        for (int i = 0; i < N; i++)
            candidate.push_back(i);

        auto result = solve(candidate, 0);

        cout << "Case #" << cases << ": " << result.second << endl;
    }
}
