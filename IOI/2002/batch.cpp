/*
Assume:
dp[j] = cost of partitioning job i to N
suffixT[j] = sum of processing time of job i to N
suffixF[j] = sum of cost factor of job i to N

Let's say we want to compute dp[i] and we already know the values of all dp[j], where i < j.

dp[i] = (S + sumT(i, j - 1))*sumF(i, j - 1) + dp[j] + (S + sumT(i, j - 1))*sumF(j, N)

The last term is necessary because the start time for the rest of the jobs (j to N) increases by S + suffixT(i, j - 1).

Simplifying the formula, we get:
dp[i] = (S + sumT(i, j - 1))*sumF(i, N) + dp[j]
dp[i] = S*suffixF[i] + (suffixT[i] - suffixT[j])*suffixF[i] + dp[j]
dp[i] = S*suffixF[i] + suffixT[i]*suffixF[i] - suffixT[j]*suffixF[i] + dp[j];
dp[i] = suffixF[i]*(-suffixT[j]) + dp[j] + (S + suffixT[i])*suffixF[i];

Can be solved with convex hull optimization.
The gradient is -suffixT[j], and the constant is dp[j]
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, S, T[MAXN + 3], F[MAXN + 3], answer;
int suffixT[MAXN + 3], suffixF[MAXN + 3];

deque<pair<int, int> > dq; //stores lines denoted by it's gradient and constant

double crossingX(pair<int, int> a, pair<int, int> b) {
    return ((double) (b.second - a.second)/(a.first - b.first));
}

void insert(int m, int c) {
    pair<int, int> newLine = make_pair(m, c);

    while (dq.size() > 1 && crossingX(dq[dq.size() - 2], dq[dq.size() - 1]) > crossingX(dq[dq.size() - 1], newLine))
        dq.pop_back();

    dq.push_back(newLine);
}

int query(int x) {
    while (dq.size() > 1 && crossingX(dq[0], dq[1]) < x)
        dq.pop_front();

    return dq[0].first * x + dq[0].second;
}

int main(){
    scanf("%d%d", &N, &S);

    for (int i = 1; i <= N; i++)
        scanf("%d%d", &T[i], &F[i]);

    suffixT[N] = T[N];
    suffixF[N] = F[N];
    for (int i = N - 1; i >= 1; i--) {
        suffixT[i] = T[i] + suffixT[i + 1];
        suffixF[i] = F[i] + suffixF[i + 1];
    }

    insert(0, 0);

    for (int i = N; i >= 1; i--) {
        int x = suffixF[i];
        int dp = query(x) + (S + suffixT[i])*suffixF[i];

        insert(-suffixT[i], dp);

        if (i == 1)
            answer = dp;
    }

    printf("%d\n", answer);
}
