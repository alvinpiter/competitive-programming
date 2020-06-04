#include<bits/stdc++.h>
using namespace std;

//last1 -> second to last, last2 -> last
struct Cashier {
    int last1, last2, cnt, idx;
    Cashier(int _last1, int _last2, int _cnt, int _idx): last1(_last1), last2(_last2), cnt(_cnt), idx(_idx) {}

    bool operator<(Cashier other) const {
        double scoreCurrent = 0;
        if (cnt == 1) scoreCurrent = last2;
        if (cnt >= 2) scoreCurrent = (last1 + last2)/2.0;
        scoreCurrent *= cnt;

        double scoreOther = 0;
        if (other.cnt == 1) scoreOther = other.last2;
        if (other.cnt >= 2) scoreOther = (other.last1 + other.last2)/2.0;
        scoreOther *= other.cnt;

        if (abs(scoreCurrent - scoreOther) < 1e-6)
            return idx > other.idx;
        else
            return scoreCurrent > scoreOther;
    }
};

int n, k;
vector<int> answer;

int main() {
    scanf("%d%d", &n, &k);

    priority_queue<Cashier> pq;
    for (int i = 1; i <= k; i++)
        pq.push(Cashier(0, 0, 0, i));

    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d", &p);

        auto cashier = pq.top(); pq.pop();

        answer.push_back(cashier.idx);

        pq.push(Cashier(cashier.last2, p, cashier.cnt + 1, cashier.idx));
    }

    for (auto a: answer)
        printf("%d ", a);
    printf("\n");
}
