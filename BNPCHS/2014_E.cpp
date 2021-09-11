#include<bits/stdc++.h>
using namespace std;

int main() {
  int tc;

  cin >> tc;
  for (int cases = 1; cases <= tc; cases++) {
    int N, M, W, Q, A[55][55], D[55];

    cin >> N >> M >> W >> Q;
    for (int i = 1; i <= N; i++) {
      cin >> D[i];
    }

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        cin >> A[i][j];
      }
    }

    cout << "Kasus #" << cases << ":\n";
    for (int q = 1; q <= Q; q++) {
      string op;

      cin >> op;
      if (op == "Q") {
        vector<pair<int, pair<int, int> > > values;
        for (int i = 1; i <= N; i++) {
          for (int j = i + 1; j <= N; j++) {
            values.push_back(make_pair(A[i][j], make_pair(i, j)));
          }
        }

        sort(values.begin(), values.end());

        int totalDuration = 0;
        set<int> answer;
        for (int i = values.size() - 1; i >= 0; i--) {
          if (answer.size() == M) {
            break;
          }

          int currentDuration = 0;
          int toBeAdded = 0;

          if (answer.find(values[i].second.first) == answer.end()) {
            currentDuration += D[values[i].second.first];
            toBeAdded++;
          }

          if (answer.find(values[i].second.second) == answer.end()) {
            currentDuration += D[values[i].second.second];
            toBeAdded++;
          }

          if (totalDuration + currentDuration <= W && answer.size() + toBeAdded <= M) {
            totalDuration += currentDuration;

            answer.insert(values[i].second.first);
            answer.insert(values[i].second.second);
          }
        }

        if (answer.size() == 0) {
          cout << 1 << endl;
          continue;
        }

        bool isFirst = true;
        for (set<int>::iterator it = answer.begin(); it != answer.end(); ++it) {
          if (!isFirst) {
            cout << " ";
          }

          cout << *it;
          isFirst = false;
        }
        cout << endl;
      } else {
        int p, q, r;
        cin >> p >> q >> r;

        A[p][q] = A[q][p] = r;
      }
    }
  }
}
