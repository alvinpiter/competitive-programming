/*
For each subtree, we'd like to employ as many ninjas while maintaining the total salary
to be less than or equal to our budget.

To do this efficiently, we need to use small-to-large merging technique. For each node,
we maintain a priority queue that stores the salaries of the ninjas in non-increasing order, and
we also maintain the sum of salaries in the priority queue.

When processing node u, we will merge the salaries from one of its children to it.
When merging, we do so from the priority queue with smaller size to priority queue with larger size.
This guarantees each salary changes the priority queue it belongs to at most O(log N) times.
Total complexity of the solution is O(N * log^2(N)).
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N, M, C[MAXN + 3], L[MAXN + 3];
vector<int> children[MAXN + 3];
priority_queue<int> salaries[MAXN + 3];
LL sumOfSalariesInPQ[MAXN + 3], ans;

// Merge data from node v to node u
void merge(int u, int v) {
  if (salaries[u].size() < salaries[v].size()) {
    swap(salaries[u], salaries[v]);
    swap(sumOfSalariesInPQ[u], sumOfSalariesInPQ[v]);
  }

  while (!salaries[v].empty()) {
    int top = salaries[v].top();

    salaries[v].pop();
    sumOfSalariesInPQ[v] -= top;

    salaries[u].push(top);
    sumOfSalariesInPQ[u] += top;
  }
}

void dfs(int u) {
  for (auto child: children[u]) {
    dfs(child);
  }

  salaries[u].push(C[u]);
  sumOfSalariesInPQ[u] = C[u];
  for (auto child: children[u]) {
    merge(u, child);
  }

  while (sumOfSalariesInPQ[u] > M) {
    int top = salaries[u].top();

    salaries[u].pop();
    sumOfSalariesInPQ[u] -= top;
  }

  ans = max(ans, (LL) salaries[u].size() * L[u]);
}

int main() {
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    int B;
    cin >> B >> C[i] >> L[i];

    children[B].push_back(i);
  }

  ans = 0;
  dfs(1);

  cout << ans << endl;
}
