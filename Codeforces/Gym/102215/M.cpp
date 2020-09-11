#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
The formula to calculate the expected pleasure is:
(p1 * v1 + p2 * v2 + ... + pn * vn)/sumV.

If we want to vote, it's better to always vote for the game with largest p.
*/

struct Game {
    int pleasure, numVotes, index;
    Game(int _pleasure, int _numVotes, int _index): pleasure(_pleasure), numVotes(_numVotes), index(_index) {}
};

bool cmpPleasure(Game a, Game b) {
    return a.pleasure > b.pleasure;
}

//compare two fractions
bool isLarger(pair<LL, LL> a, pair<LL, LL> b) {
    return a.first * b.second > a.second * b.first;
}

pair<LL, LL> simplify(pair<LL, LL> p) {
    LL gcd = __gcd(p.first, p.second);
    return make_pair(p.first/gcd, p.second/gcd);
}

int t, n;
vector<Game> games;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        games.clear();

        int totalVotes = 0;
        int totalPleasureXVotes = 0;
        for (int i = 0; i < n; i++) {
            int p, v;
            cin >> p >> v;

            games.push_back(Game(p, v, i));
            totalVotes += v;
            totalPleasureXVotes += p*v;
        }

        sort(games.begin(), games.end(), cmpPleasure);

        pair<LL, LL> bestEV = make_pair(0, 1); //best expected pleasure
        int cntBest = 0; //number of votes in best scenario

        for (int i = 0; i < n; i++) {
            totalVotes += 1;
            totalPleasureXVotes += games[i].pleasure;

            pair<LL, LL> currentEV = simplify(make_pair(totalPleasureXVotes, totalVotes));

            if (isLarger(currentEV, bestEV)) {
                bestEV = currentEV;
                cntBest = i + 1;
            }
        }

        cout << bestEV.first << "/" << bestEV.second << endl;
        cout << cntBest << endl;
        for (int i = 0; i < cntBest; i++) {
            cout << games[i].index + 1;
            if (i == cntBest - 1)
                cout << endl;
            else
                cout << " ";
        }
    }
}
