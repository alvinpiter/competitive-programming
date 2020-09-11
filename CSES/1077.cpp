#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, K, X[MAXN + 3];
LL sumLows, sumHighs, answer[MAXN + 3];
multiset<int> lows, highs;

void insert(int x) {
    if (lows.size() > 0 && x <= *lows.rbegin()) {
        lows.insert(x);
        sumLows += x;
    } else {
        highs.insert(x);
        sumHighs += x;
    }
}

void remove(int x) {
    if (lows.find(x) != lows.end()) {
        lows.erase(lows.find(x));
        sumLows -= x;
    } else {
        highs.erase(highs.find(x));
        sumHighs -= x;
    }
}

void balance() {
    while ((int) lows.size() - (int) highs.size() > 1) {
        int m = *(lows.rbegin());

        lows.erase(lows.find(m));
        sumLows -= m;

        highs.insert(m);
        sumHighs += m;
    }

    while ((int) highs.size() - (int) lows.size() > 0) {
        int m = *(highs.begin());

        highs.erase(highs.find(m));
        sumHighs -= m;

        lows.insert(m);
        sumLows += m;
    }
}

int getMedian() {
    return *(lows.rbegin());
}

LL getCost() {
    LL m = (LL) getMedian();
    int lowsSize = (int) lows.size();
    int highsSize = (int) highs.size();

    return (m * lowsSize - sumLows) + (sumHighs - m * highsSize);
}

int main() {
    cin >> N >> K;

    sumLows = sumHighs = 0;
    for (int i = 1; i <= N; i++) {
        cin >> X[i];

        if (i > K)
            remove(X[i - K]);

        insert(X[i]);
        balance();

        answer[i] = getCost();
    }

    for (int i = K; i <= N; i++) {
        if (i > K)
            cout << " ";

        cout << answer[i];
    }
    cout << endl;
}
