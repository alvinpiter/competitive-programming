#include<bits/stdc++.h>
using namespace std;

int main() {
  int tc, N;
  string word;
  map<string, int> counter;

  cin >> tc;
  for (int cases = 1; cases <= tc; cases++) {
    cin >> N;

    counter.clear();
    for (int i = 1; i <= N; i++) {
      cin >> word;
      sort(word.begin(), word.end());

      if (counter.find(word) != counter.end()) {
        counter[word] += 1;
      } else {
        counter[word] = 1;
      }
    }

    int ans = 0;
    for (map<string, int>::iterator it = counter.begin(); it != counter.end(); ++it) {
      int ctr = it->second;
      ans += (ctr * (ctr - 1))/2;
    }

    cout << "Kasus #" << cases << ": " << ans << endl;
  }
}
