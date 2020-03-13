#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, K, X[MAXN + 3], medians[MAXN + 3];
multiset<int> lows, highs;

void insert(int x) {
    if (lows.size() > 0 && x <= *lows.rbegin())
        lows.insert(x);
    else
        highs.insert(x);
}

void remove(int x) {
    if (lows.find(x) != lows.end()) {
        lows.erase(lows.find(x));
    } else {
        highs.erase(highs.find(x));
    }
}

void balance() {
    while ((int) lows.size() - (int) highs.size() > 1) {
        int m = *(lows.rbegin());
        lows.erase(lows.find(m));
        highs.insert(m);
    }

    while ((int) highs.size() - (int) lows.size() > 0) {
        int m = *(highs.begin());
        highs.erase(highs.find(m));
        lows.insert(m);
    }
}

int getMedian() {
    return *(lows.rbegin());
}

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> X[i];

        if (i > K)
            remove(X[i - K]);

        insert(X[i]);
        balance();

        medians[i] = getMedian();
    }

    for (int i = K; i <= N; i++) {
        if (i > K)
            cout << " ";

        cout << medians[i];
    }
    cout << endl;
}
