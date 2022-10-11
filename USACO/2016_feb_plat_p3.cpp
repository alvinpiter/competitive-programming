/*
To make the problem easier to solve, let's treat the barns as 1-dimensional, i.e we don't need to
think about circling the cows. We can do so by pivoting the barns on the first barn whose exterior door
is open. For example, if the first barn whose exterior door is open is the second one, then our barns order
will be: 2 3 4 5 1.

Define dp[i][k] as the minimal total walk by the cows if we only consider the i-th barn up to the last barn,
and the i-th barn's exterior door is open and we may open k more exterior doors. The answer to the 1-dimensional problem will
be dp[1][K - 1].

Transition:
dp[i][k] = min(cost(i, j - 1) + dp[j][k - 1]), where i < j and cost(i, j - 1) is the cost of moving cows from the i-th barn upto
the (j - 1)-th barn.

cost(i, j - 1) can be formulated as follow: (wsum[j - 1] - wsum[i - 1]) - i * (sum[j - 1] - sum[i - 1]), where:
* wsum[j] = sigma(r[k] * k)
* sum[j] = sigma(r[k])

dp[i][k] = min(
  i * sum[i - 1] - wsum[i - 1] + (i * -sum[j - 1] + dp[j][k - 1] + wsum[j - 1])
)

Notice that the calculation can be speed up by convex hull trick. The lines in the convex hull will
have -sum[j - 1] as its gradient and dp[j][k - 1] + wsum[j - 1] as its constant.

The lines are added to the convex hull starting from the one with the largest gradient. We can maintain the upper hull
of the lines.

Total complexity will be O(n^2 * k), O(nk) for solving each of the 1-dimensional problem, and O(n) for n 1-dimensional
problems.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000000000000000LL
#define MAXN 1000
#define MAXK 7

struct Line {
  LL m, c;
  Line(LL m_, LL c_): m(m_), c(c_) {}
};

class UpperHull {
private:
  vector<Line> lines; // {m, c}
  int ptrBest = 0;

  LL eval(Line line, LL x) {
    return line.m * x + line.c;
  }

  // Check whether prevLine is obsolete
  bool checkObsolete(Line prevPrevLine, Line prevLine, Line newLine) {
    /*
    prevLine is obsolete if the x-coordinate of intersection between the newLine and the prevLine
    is smaller than the x-coordinate of intersection between the prevPrevLine and prevLine

    x-coordinate of the intersection of newLine and prevLine:
    x = (prevLine.c - newLine.c)/(newLine.m - prevLine.m)

    x-coordinate of the intersection of prevPrevLine and prevLine:
    x = (prevLine.c - prevPrevLine.c)/(prevPrevLine.m - prevLine.m)
    */

    return (prevLine.c - newLine.c) * (prevPrevLine.m - prevLine.m) < (prevLine.c - prevPrevLine.c) * (newLine.m - prevLine.m);
  }

public:
  void insert(LL m, LL c) {
    while (lines.size() >= 2 && checkObsolete(lines[lines.size() - 2], lines[lines.size() - 1], Line(m, c))) {
      lines.pop_back();
    }

    lines.push_back(Line(m, c));
  }

  LL query(LL x) {
    // IMPORTANT
    ptrBest = min(ptrBest, (int) lines.size() - 1);

    while (ptrBest + 1 < lines.size() && eval(lines[ptrBest + 1], x) < eval(lines[ptrBest], x)) {
      ptrBest += 1;
    }

    return eval(lines[ptrBest], x);
  }
};

LL solve1D(vector<int>& r, int K) {
  int N = (int) r.size();
  LL sum[MAXN + 3], wsum[MAXN + 3], dp[MAXN + 3][MAXK + 3];

  sum[0] = wsum[0] = 0;
  for (int i = 1; i <= N; i++) {
    sum[i] = sum[i - 1] + r[i - 1];
    wsum[i] = wsum[i - 1] + r[i - 1] * i;
  }

  // Base case
  dp[N + 1][0] = 0;
  for (int i = 1; i <= N; i++) {
    dp[i][0] = (wsum[N] - wsum[i - 1]) - (sum[N] - sum[i - 1]) * i;
  }

  for (int k = 1; k < K; k++) {
    dp[N + 1][k] = 0;

    UpperHull uhull;
    uhull.insert(-sum[N], dp[N + 1][k - 1] + wsum[N]); // dp[N + 1][k - 1]
    for (int i = N; i >= 1; i--) {
      dp[i][k] = sum[i - 1] * i - wsum[i - 1] + uhull.query(i);
      uhull.insert(-sum[i - 1], dp[i][k - 1] + wsum[i - 1]);
    }
  }

  return dp[1][K - 1];
}

int main() {
  freopen("cbarn.in", "r", stdin);
  freopen("cbarn.out", "w", stdout);

  int n, k, r[MAXN + 3];

  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> r[i];
  }

  LL mini = INF;
  for (int i = 0; i < n; i++) {
    // Treat the i-th barn as the first barn to have its exterior door open
    vector<int> flatR;
    flatR.push_back(r[i]);
    for (int j = (i + 1)%n; j != i; j = (j + 1)%n) {
      flatR.push_back(r[j]);
    }

    mini = min(mini, solve1D(flatR, k));
  }

  cout << mini << endl;
}
