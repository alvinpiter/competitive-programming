#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Let's simplify the array to be -1 (spotted) and 1 (white). We want to find largest segment
whose sum is >= 0 and is even. Sum of segment i..j can be written as prefixSum[j] - prefixSum[i - 1].
Since we want the difference is even, the parity of the prefix sum must be the same.
*/

bool isEven(int num) {
    return abs(num)%2 == 0;
}

int N, answer;
pair<int, int> cows[MAXN + 3];
vector<pair<int, int> > oddPrefixes, evenPrefixes; //{value, index};

int main() {
    freopen("fairphoto.in", "r", stdin);
    freopen("fairphoto.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int pos;
        string typ;
        cin >> pos >> typ;

        cows[i] = {pos, (typ == "S" ? -1 : 1)};
    }

    sort(cows + 1, cows + N + 1);

    int prefixSum = 0;
    evenPrefixes.push_back({0, 0});

    for (int i = 1; i <= N; i++) {
        prefixSum += cows[i].second;
        if (isEven(prefixSum))
            evenPrefixes.push_back({prefixSum, i});
        else
            oddPrefixes.push_back({prefixSum, i});
    }

    sort(evenPrefixes.begin(), evenPrefixes.end());
    sort(oddPrefixes.begin(), oddPrefixes.end());

    answer = 0;

    if (!evenPrefixes.empty()) {
        int miniPos = evenPrefixes[0].second;
        for (int i = 1; i < evenPrefixes.size(); i++) {
            int pos = evenPrefixes[i].second;
            if (miniPos < pos)
                answer = max(answer, cows[pos].first - cows[miniPos + 1].first);

            miniPos = min(miniPos, pos);
        }
    }

    if (!oddPrefixes.empty()) {
        int miniPos = oddPrefixes[0].second;
        for (int i = 1; i < oddPrefixes.size(); i++) {
            int pos = oddPrefixes[i].second;
            if (miniPos < pos)
                answer = max(answer, cows[pos].first - cows[miniPos + 1].first);

            miniPos = min(miniPos, pos);
        }
    }

    cout << answer << endl;
}
