/*
Assume prev(a) and next(b) are connected.

small(a, b) -> The index of city c (either a or b) such that cities a..b component is connected to
prev(a)-next(b) via prev(a).

large(a, b) -> The index of city c (either a or b) such that cities a..b component is connected to
prev(a)-next(b) via next(b).

If there is no such city c and cities a..b is not an empty set, return -1.
If there is no such city c and cities a..b is an empty set, return n.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int n, m, mat[MAXN + 3][MAXN + 3];
int smallCache[MAXN + 3][MAXN + 3], largeCache[MAXN + 3][MAXN + 3];

int small(int a, int b);
int large(int a, int b);

int prev(int a) {
  return (a - 1 + n)%n;
}

int next(int a) {
  return (a + 1)%n;
}

int small(int a, int b) {
  if (a > b) {
    return n;
  }

  if (smallCache[a][b] != -2) {
    return smallCache[a][b];
  }

  smallCache[a][b] = -1;

  if (mat[prev(a)][a] && small(a + 1, b) != -1) {
    smallCache[a][b] = a;
  }

  if (mat[prev(a)][b] && large(a, b - 1) != -1) {
    smallCache[a][b] = b;
  }

  return smallCache[a][b];
}

int large(int a, int b) {
  if (a > b) {
    return n;
  }

  if (largeCache[a][b] != -2) {
    return largeCache[a][b];
  }

  largeCache[a][b] = -1;

  if (mat[a][next(b)] && small(a + 1, b) != -1) {
    largeCache[a][b] = a;
  }

  if (mat[b][next(b)] && large(a, b - 1) != -1) {
    largeCache[a][b] = b;
  }

  return largeCache[a][b];
}

vector<int> traceSolution(int a, int b, bool followSmall) {
  vector<int> result;
  while (a <= b) {
    if (followSmall) {
      if (small(a, b) == a) {
        result.push_back(a);
        a = a + 1;
      } else if (small(a, b) == b) {
        result.push_back(b);
        b = b - 1;
        followSmall = false;
      }
    } else {
      if (large(a, b) == a) {
        result.push_back(a);
        a = a + 1;
        followSmall = true;
      } else if (large(a, b) == b) {
        result.push_back(b);
        b = b - 1;
      }
    }
  }

  return result;
}

vector<int> buildSolution() {
  vector<int> result;
  for (int p = 0; p < n; p++) {
    if (mat[0][p]) {
      if (small(1, p - 1) != -1 && small(p + 1, n - 1) != -1) {
        vector<int> first = traceSolution(1, p - 1, true);
        reverse(first.begin(), first.end());

        vector<int> second = traceSolution(p + 1, n - 1, true);

        for (auto v: first) result.push_back(v);
        result.push_back(0);
        result.push_back(p);
        for (auto v: second) result.push_back(v);

        return result;
      }

      if (large(1, p - 1) != -1 && large(p + 1, n - 1) != -1) {
        vector<int> first = traceSolution(1, p - 1, false);
        reverse(first.begin(), first.end());

        vector<int> second = traceSolution(p + 1, n - 1, false);

        for (auto v: first) result.push_back(v);
        result.push_back(p);
        result.push_back(0);
        for (auto v: second) result.push_back(v);

        return result;
      }
    }
  }

  return result;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;

    a--; b--;
    mat[a][b] = mat[b][a] = true;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      smallCache[i][j] = -2;
      largeCache[i][j] = -2;
    }
  }
  vector<int> result = buildSolution();

  if (result.size() < n) {
    cout << -1 << endl;
  } else {
    for (int i = 0; i < result.size(); i++) {
      if (i > 0) {
        cout << " ";
      }
      cout << result[i] + 1;
    }
    cout << endl;
  }
}
