#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, answer;
    string s, genome;

    cin >> n >> s;

    answer = 1e9;
    genome = "ACTG";
    for (int i = 0; i + 3 < (int) s.length(); i++) {
        int cost = 0;
        for (int j = 0; j < 4; j++) {
            int diff = abs(genome[j] - s[i + j]);
            cost += min(diff, 26 - diff);
        }

        answer = min(answer, cost);
    }

    cout << answer << endl;
}
