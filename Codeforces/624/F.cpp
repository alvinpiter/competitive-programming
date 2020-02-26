#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

class BIT {
private:
    int sz;
    LL arr[MAXN + 3];

public:
    BIT(int _sz) { sz = _sz; memset(arr, 0, sizeof(arr)); }
    void update(int idx, int val) {
        while (idx <= sz) {
            arr[idx] += val;
            idx += (idx & -idx);
        }
    }

    LL query(int idx) {
        LL sum = 0;
        while (idx > 0) {
            sum += arr[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    LL rmq(int a, int b) {
        return query(b) - query(a - 1);
    }
};

int N, x[MAXN + 3], v[MAXN + 3];
vector<int> uniqueSpeed;
pair<int, int> points[MAXN + 3]; //(position, speed)
LL answer;

int normalize(int speed) {
    return (lower_bound(uniqueSpeed.begin(), uniqueSpeed.end(), speed) - uniqueSpeed.begin()) + 1;
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> x[i];

    for (int i = 1; i <= N; i++) {
        cin >> v[i];
        uniqueSpeed.push_back(v[i]);
    }

    sort(uniqueSpeed.begin(), uniqueSpeed.end());
    uniqueSpeed.resize(unique(uniqueSpeed.begin(), uniqueSpeed.end()) - uniqueSpeed.begin());

    for (int i = 1; i <= N; i++)
        points[i] = make_pair(x[i], v[i]);

    sort(points + 1, points + N + 1);

    BIT bitX(uniqueSpeed.size());
    BIT bitCount(uniqueSpeed.size());

    for (int i = N; i >= 1; i--) {
        int idx = normalize(points[i].second);
        bitX.update(idx, points[i].first);
        bitCount.update(idx, 1);
    }

    answer = 0;
    for (int i = 1; i <= N; i++) {
        int idx = normalize(points[i].second);

        bitX.update(idx, -points[i].first);
        bitCount.update(idx, -1);

        answer += (bitX.rmq(idx, uniqueSpeed.size()) - (LL) points[i].first * bitCount.rmq(idx, uniqueSpeed.size()));
    }

    cout << answer << endl;
}
