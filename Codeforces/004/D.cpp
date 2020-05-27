#include<bits/stdc++.h>
using namespace std;

struct Envelope {
    int width, height, index;
    Envelope(int _w, int _h, int _idx): width(_w), height(_h), index(_idx) {}
};

bool cmp(Envelope a, Envelope b) {
    return a.width < b.width;
}

int main() {
    int n, cardWidth, cardHeight, dp[5003], sol[5003];
    vector<Envelope> envs;

    cin >> n >> cardWidth >> cardHeight;
    for (int i = 0; i < n; i++) {
        int w, h;
        cin >> w >> h;

        envs.push_back(Envelope(w, h, i));
    }

    sort(envs.begin(), envs.end(), cmp);

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1;
        sol[i] = -1;

        for (int j = i + 1; j < n; j++) {
            if (envs[j].width > envs[i].width && envs[j].height > envs[i].height && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                sol[i] = j;
            }
        }
    }

    int bestStartingPoint = -1;
    for (int i = 0; i < n; i++) {
        if (envs[i].width > cardWidth && envs[i].height > cardHeight) {
            if (bestStartingPoint == -1 || dp[i] > dp[bestStartingPoint])
                bestStartingPoint = i;
        }
    }

    vector<int> indices;

    int current = bestStartingPoint;
    while (current != -1) {
        indices.push_back(envs[current].index);
        current = sol[current];
    }

    if (indices.empty())
        cout << 0 << endl;
    else {
        cout << indices.size() << endl;
        for (auto idx: indices)
            cout << idx + 1 << " ";
        cout << endl;
    }
}
