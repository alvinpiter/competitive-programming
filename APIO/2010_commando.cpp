/*
dp[j] = Maximum score achievable out of the first j soldiers.

dp[j] = dp[i] + a * (sum[j] - sum[i])^2 + b * (sum[j] - sum[i]) + c, for some i < j.
dp[j] = dp[i] + a * sum[j]^2 + a * sum[i]^2 - 2 * a * sum[i] * sum[j] + b * sum[j] - b * sum[i] + c
dp[j] = (-2 * a * sum[i]) * sum[j] + (dp[i] + a * sum[i]^2 - b * sum[i]) + (a * sum[j]^2 + b * sum[j] + c)

Notice that the last term is constant for some j, hence we would like to maximize the first two terms.

We can solve this using convex hull trick where the lines equation, y = mx + c, are:
* The gradient, m: -2 * a * sum[i]
* The constant, c: dp[i] + a * sum[i]^2 - b * sum[i]

For a given x, namely sum[j], we would like to know the line which yield maximum value.

Also notice that the lines have increasing gradient, hence we will maintain the lower convex hull, i.e the U shape.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int

struct Line {
  LL m, c;
  Line(LL m_, LL c_): m(m_), c(c_) {}
};

vector<Line> lines;
int ptrBest = 0;

LL evaluate(Line line, LL x) {
  return line.m * x + line.c;
}

bool checkObsolete(Line prevPrevLine, Line prevLine, Line line) {
  /*
  prevPrevLine and line crosses at x1 = (line.c - prevPrevLine.c)/(prevPrevLine.m - line.m);
  prevLine and line crosses at x2 = (line.c - prevLine.c)/(prevLine.m - line.m);

  prevLine is obsolete if x2 < x1.
  */
  return (line.c - prevLine.c) * (prevPrevLine.m - line.m) < (line.c - prevPrevLine.c) * (prevLine.m - line.m);
}

void insert(Line line) {
  while (lines.size() > 1) {
    if (checkObsolete(lines[lines.size() - 2], lines[lines.size() - 1], line)) {
      lines.pop_back();
    } else {
      break;
    }
  }

  lines.push_back(line);
}

LL query(LL x) {
  while (ptrBest + 1 < lines.size() && evaluate(lines[ptrBest + 1], x) > evaluate(lines[ptrBest], x)) {
    ptrBest += 1;
  }

  return evaluate(lines[ptrBest], x);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  int n;
  LL a, b, c, x, currentPrefixSum, ans;

  cin >> n >> a >> b >> c;

  currentPrefixSum = 0;

  // Insert the base case, dp[0] = 0
  insert(Line(0, 0));

  for (int i = 1; i <= n; i++) {
    cin >> x;

    currentPrefixSum += x;
    ans = query(currentPrefixSum) + (a * currentPrefixSum * currentPrefixSum + b * currentPrefixSum + c);

    insert(Line(
      -2 * a * currentPrefixSum,
      ans + a * currentPrefixSum * currentPrefixSum - b * currentPrefixSum
    ));
  }

  cout << ans << endl;
}
