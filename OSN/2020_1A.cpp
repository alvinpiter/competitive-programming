#include<bits/stdc++.h>
using namespace std;
#define MAXK 100000

int N, M, K, A[MAXK + 3];

int stat[MAXK + 3];
bool foundSolutionForSubtask;

struct Rect {
  int x1, y1, x2, y2;
  Rect(int _x1, int _y1, int _x2, int _y2): x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

bool rectsComparator(pair<int, Rect> r1, pair<int, Rect> r2) {
  return r1.first < r2.first;
}

void printRects(vector<pair<int, Rect> > rects) {
  sort(rects.begin(), rects.end(), rectsComparator);
  for (int i = 0; i < rects.size(); i++) {
    Rect rect = rects[i].second;

    cout << rect.x1 << " " << rect.x2 << " " << rect.y1 << " " << rect.y2 << endl;
  }
}

void solve1() {
  cout << "0 1 0 4" << endl;
  cout << "0 4 4 5" << endl;
  cout << "4 5 1 5" << endl;
  cout << "1 5 0 1" << endl;
  cout << "1 4 1 4" << endl;
}

void solve2() {
  cout << "2 3 3 5" << endl;
  cout << "0 3 5 6" << endl;
  cout << "0 2 3 5" << endl;
  cout << "0 5 6 7" << endl;
  cout << "3 4 0 6" << endl;
  cout << "4 5 0 6" << endl;
  cout << "5 6 0 7" << endl;
  cout << "0 3 0 3" << endl;
}

void solve3() {
  /*
  Just stack rectangles with width 1 and height Ai on top of each other
  */

  int currentY = 0;
  for (int i = 1; i <= K; i++) {
    int x1 = 0, y1 = currentY, x2 = 1, y2 = currentY + A[i];
    cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;

    currentY += A[i];
  }
}

void solve4() {
  /*
  1xN on the bottom.
  Then put kx1 and (N - k)x1 on the second row and so on.
  */
  vector<pair<int, Rect> > rects;

  rects.push_back(make_pair(N, Rect(0, 0, N, 1)));
  for (int y = 1; y <= 49999; y++) {
    rects.push_back(make_pair(y, Rect(0, y, y, y + 1)));
    rects.push_back(make_pair(N - y, Rect(y, y, N, y + 1)));
  }

  printRects(rects);
}

void solve5() {
  /*
  All rectangles will have width = 9973 and height = 99991.
  We will have 293 of these rectangles horizontally and 311 vertically.
  */
  vector<pair<int, Rect> > rects;
  for (int y = 0; y < 99991 * 311; y += 99991) {
    for (int x = 0; x < 9973 * 293; x += 9973) {
      //rectangle id doesn't matter here, so just use 1
      rects.push_back(make_pair(1, Rect(x, y, x + 9973, y + 99991)));
    }
  }

  printRects(rects);
}

void constructSubtask67Solution() {
  vector<pair<int, Rect> > rects;

  int baseY = 0; //Sum of all heights of rectangles with width 2
  for (int i = 1; i <= K; i++) {
    if (stat[i] == 2) {
      rects.push_back(make_pair(i, Rect(0, baseY, 2, baseY + A[i]/2)));
      baseY += A[i]/2;
    }
  }

  int currentY = baseY;
  for (int i = 1; i <= K; i++) {
    if (stat[i] == 1) {
      rects.push_back(make_pair(i, Rect(0, currentY, 1, currentY + A[i])));
      currentY += A[i];
    }
  }

  currentY = baseY;
  for (int i = 1; i <= K; i++) {
    if (stat[i] == 0) {
      rects.push_back(make_pair(i, Rect(1, currentY, 2, currentY + A[i])));
      currentY += A[i];
    }
  }

  printRects(rects);
}

void solve6Rec(int idx, int totalLength) {
  if (totalLength == M) {
    constructSubtask67Solution();
    foundSolutionForSubtask = true;

    return;
  }

  if (idx == K + 1 || totalLength > M || foundSolutionForSubtask) {
    return;
  }

  stat[idx] = 0;
  solve6Rec(idx + 1, totalLength);

  stat[idx] = 1;
  solve6Rec(idx + 1, totalLength + A[idx]);

  if (A[idx] % 2 == 0) {
    stat[idx] = 2;
    solve6Rec(idx + 1, totalLength + A[idx]/2);
  }

  stat[idx] = 0;
}

void solve6() {
  /*
  Solve recursively, per column.

  Define stat[i]:
  0 -> Not used in first column (it will later be used in second column, with width 1)
  1 -> Used in first column with width 1
  2 -> Used with width 2
  */
  memset(stat, 0, sizeof(stat));
  foundSolutionForSubtask = false;

  solve6Rec(1, 0);
}

void solve7() {
  /*
  Similar with subtask 6, but now use DP.
  dp[k][sum] => Can we reach sum using the first k areas.
  */

  bool dp[103][10003];
  int sol[103][10003];

  memset(dp, false, sizeof(dp));
  dp[0][0] = true;

  for (int i = 1; i <= K; i++) {
    for (int sum = 1; sum <= M; sum++) {
      if (dp[i - 1][sum]) {
        //don't need current area
        dp[i][sum] = true;
        sol[i][sum] = 0;
      } else if (sum >= A[i] && dp[i - 1][sum - A[i]]) {
        //Take current area as rect with width 1
        dp[i][sum] = true;
        sol[i][sum] = 1;
      } else if (A[i]%2 == 0 && sum >= A[i]/2 && dp[i - 1][sum - A[i]/2]) {
        //Take current area as rect width 2
        dp[i][sum] = true;
        sol[i][sum] = 2;
      } else {
        //Can't reach this state
        dp[i][sum] = false;
        sol[i][sum] = -1;
      }
    }
  }

  int currentIdx = K, currentSum = M;
  while (currentIdx > 0) {
    stat[currentIdx] = sol[currentIdx][currentSum];

    if (sol[currentIdx][currentSum] == 0) {
      currentIdx -= 1;
    } else if (sol[currentIdx][currentSum] == 1) {
      currentSum -= A[currentIdx];
      currentIdx -= 1;
    } else if (sol[currentIdx][currentSum] == 2) {
      currentSum -= A[currentIdx]/2;
      currentIdx -= 1;
    }
  }

  constructSubtask67Solution();
}

void solve8() {
  /*
  4681 = 2^0 + 2^3 + 2^6 + 2^9 + 2^12
  229383 = 2^0 + 2^1 + 2^2 + 2^15 + 2^16 + 2^17

  Divide the width into 5 parts, each with width 2^0, 2^3, and so on.
  Divide the height into 6 parts, each with width 2^0, 2^1, and so on.

  There will be 30 regions each with different area.
  */
  int widthOnBits[] = { 0, 3, 6, 9, 12} ;
  int heightOnBits[] = { 0, 1, 2, 15, 16, 17 };

  vector<pair<int, Rect> > rects;

  int currentY = 0;
  for (int h = 0; h < 6; h++) {

    int currentX = 0;
    for (int w = 0; w < 5; w++) {
      int index = heightOnBits[h] + widthOnBits[w];

      rects.push_back(make_pair(
        index,
        Rect(currentX, currentY, currentX + (1 << widthOnBits[w]), currentY + (1 << heightOnBits[h]))));

      currentX += (1 << widthOnBits[w]);
    }

    currentY += (1 << heightOnBits[h]);
  }

  printRects(rects);
}

int fibo[25];
void solve9Rec(int idx, int x1, int y1, int x2, int y2, int direction, vector<pair<int, Rect> >& rects) {
  if (idx == 0) {
    return;
  }

  rects.push_back(make_pair(idx, Rect(x1, y1, x2, y2)));

  int newDirection = (direction + 1)%4;
  if (direction == 0) {
    //goes up from right most
    solve9Rec(idx - 1, x2 - fibo[idx - 1], y2, x2, y2 + fibo[idx - 1], newDirection, rects);
  } else if (direction == 1) {
    //goes left from top most
    solve9Rec(idx - 1, x1 - fibo[idx - 1], y2 - fibo[idx - 1], x1, y2, newDirection, rects);
  } else if (direction == 2) {
    //goes down from left most
    solve9Rec(idx - 1, x1, y1 - fibo[idx - 1], x1 + fibo[idx - 1], y1, newDirection, rects);
  } else if (direction == 3) {
    //goes righ from bottom most
    solve9Rec(idx - 1, x2, y1, x2 + fibo[idx - 1], y1 + fibo[idx - 1], newDirection, rects);
  }
}

void solve9() {
  vector<pair<int, Rect> > rects;

  fibo[1] = fibo[2] = 1;
  for (int i = 3; i <= 23; i++) {
    fibo[i] = fibo[i - 1] + fibo[i - 2];
  }

  solve9Rec(23, 0, 0, 28657, 28657, 3, rects);

  printRects(rects);
}

int main() {
  cin >> N >> M >> K;
  for (int i = 1; i <= K; i++) {
    cin >> A[i];
  }

  solve9();
}
