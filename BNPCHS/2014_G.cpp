#include<bits/stdc++.h>
using namespace std;
#define MAXN 40000

int main() {
  int tc;

  cin >> tc;
  for (int cases = 1; cases <= tc; cases++) {
    int M, N, h[MAXN + 3];
    multiset<int> firstHalf, secondHalf;

    cin >> M >> N;
    for (int i = 1; i <= M; i++) {
      cin >> h[i];
    }

    for (int i = 1; i <= N/2; i++) {
      firstHalf.insert(h[i]);
    }

    for (int i = N/2 + 1; i <= N; i++) {
      secondHalf.insert(h[i]);
    }

    int answer = 0;
    for (int i = 1; i + N - 1 <= M; i++) {
      int maxInFirstHalf = *(--firstHalf.end());
      int maxInSecondHalf = *(--secondHalf.end());

      if (maxInFirstHalf == maxInSecondHalf) {
        answer += 1;
      }

      firstHalf.erase(firstHalf.find(h[i]));
      firstHalf.insert(h[i + N/2]);

      secondHalf.erase(secondHalf.find(h[i + N/2]));
      secondHalf.insert(h[i + N]);
    }

    cout << "Kasus #" << cases << ": " << answer << endl;
  }
}
