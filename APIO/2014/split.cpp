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

The code is very very messy. Will clean it up later.
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

int N, K;
LL prefix[MAXN + 3], dp[MAXN + 3][2];
int sol[MAXN + 3][MAXK + 3];

int front, back;
Line lines[MAXN + 3];

LL ops = 0;

double crossingX(Line a, Line b) {
    return ((double) (b.constant - a.constant)/(a.gradient - b.gradient));
}

void insert(LL gradient, LL constant, LL index) {
    Line line(gradient, constant, index);

    bool shouldAdd = true;
    while (true) {
        if (DEBUG) ops += 1;

        if (front - back + 1 == 0)
            break;

        if (line.gradient == lines[front].gradient) {
            if (line.constant > lines[front].constant)
                front -= 1;
            else {
                shouldAdd = false;
                break;
            }
        } else if (front - back + 1 > 1 && crossingX(lines[front - 1], lines[front]) > crossingX(lines[front], line)) {
            front -= 1;
        } else
            break;
    }

    if (shouldAdd) {
        front += 1;
        lines[front] = line;
    }
}

Line query(LL x) {
    while (front - back + 1 > 1 && crossingX(lines[back], lines[back + 1]) < x) {
        if (DEBUG) ops += 1;
        back += 1;
    }

    return lines[back];
}

void printSolution() {
    vector<int> solution;
    int currentN = N;
    int currentK = K;
    while (true) {
        if (DEBUG) ops += 1;
        int s = sol[currentN][currentK];

        if (s > 0)
            solution.push_back(s);
        else
            break;

        currentN = s;
        currentK -= 1;
    }

    for (int i = 0; i < solution.size(); i++) {
        if (DEBUG) ops += 1;
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
        front = 0;
        back = 1;

        t = 1 - t;
        dp[1][t] = -INF;
        for (int n = 2; n <= N; n++) {
            if (DEBUG) ops += 1;
            insert(prefix[n - 1], dp[n - 1][1 - t] - prefix[n - 1]*prefix[n - 1], n - 1);

            Line best = query(prefix[n]);

            dp[n][t] = best.gradient * prefix[n] + best.constant;
            sol[n][k] = best.index;
        }
    }

    printf("%lld\n", dp[N][t]);
    printSolution();

    if (DEBUG) cout << "ops: " << ops << endl;
}
