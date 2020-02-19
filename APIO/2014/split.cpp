/*
Observation: the order of partitioning does not matter. It can be proven by exchange argument.

dp[n][k] = max point reachable from the first n numbers if we want to split it into k partitions.
dp[n][k] = max(dp[m][k - 1] + sum(1, m) * sum(m + 1, n)), for m < n

We need to speed up the computation by using convex hull trick. Final complexity would be O(NK).
Be careful because the gradient might be the same.
In case the gradient is the same, take the line with larger constant.

sample tc:
4 1
6 0 1 16
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MAXK 200
#define INF 1000000000000000000LL
#define DEBUG false

struct Line {
    LL gradient, constant, index;
    Line() {}
    Line(LL g, LL c, LL i): gradient(g), constant(c), index(i) {}
};

//STL's deque got TLE
class MyDeque {
private:
    int idxFront, idxBack;
    Line values[MAXN + 3];

public:
    MyDeque() {
        idxFront = 0;
        idxBack = 1;
    }

    void clear() { idxFront = 0; idxBack = 1; }
    int size() { return idxFront - idxBack + 1; }

    Line back() { return values[idxBack]; }
    Line secondBack() { return values[idxBack + 1]; }
    void popBack() { ++idxBack; }

    Line front() { return values[idxFront]; }
    Line secondFront() { return values[idxFront - 1]; }
    void pushFront(Line l) { values[++idxFront] = l; }
    void popFront() { --idxFront; }
} dq;

int N, K;
LL prefix[MAXN + 3], dp[MAXN + 3][2];
int sol[MAXN + 3][MAXK + 3];

double crossingX(Line a, Line b) {
    return ((double) (b.constant - a.constant)/(a.gradient - b.gradient));
}

void insert(LL gradient, LL constant, LL index) {
    Line line(gradient, constant, index);

    while (true) {
        if (dq.size() == 0)
            break;

        if (line.gradient == dq.front().gradient) {
            if (line.constant > dq.front().constant)
                dq.popFront();
            else
                return;
        } else if (dq.size() > 1 && crossingX(dq.secondFront(), dq.front()) > crossingX(dq.front(), line))
            dq.popFront();
        else
            break;
    }

    dq.pushFront(line);
}

Line query(LL x) {
    while (dq.size() > 1 && crossingX(dq.back(), dq.secondBack()) < x)
        dq.popBack();

    return dq.back();
}

void printSolution() {
    vector<int> solution;
    int currentN = N;
    int currentK = K;
    while (true) {
        int s = sol[currentN][currentK];

        if (s > 0)
            solution.push_back(s);
        else
            break;

        currentN = s;
        currentK -= 1;
    }

    for (int i = 0; i < solution.size(); i++) {
        if (i > 0)
            printf(" ");

        printf("%d", solution[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &N, &K);
    K += 1;

    prefix[0] = 0;
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);

        prefix[i] = prefix[i - 1] + a;
    }

    int t = 0;

    //dp[n][1] = 0
    for (int n = 1; n <= N; n++)
        dp[n][t] = 0;

    for (int k = 2; k <= K; k++) {
        dq.clear();

        t = 1 - t;
        dp[1][t] = -INF;
        for (int n = 2; n <= N; n++) {
            insert(prefix[n - 1], dp[n - 1][1 - t] - prefix[n - 1]*prefix[n - 1], n - 1);

            Line best = query(prefix[n]);

            dp[n][t] = best.gradient * prefix[n] + best.constant;
            sol[n][k] = best.index;
        }
    }

    printf("%lld\n", dp[N][t]);
    printSolution();
}
