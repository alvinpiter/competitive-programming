/*
For each row:
* Find the ranges of lasers that can be seen
* Merge all those ranges
* The complement of those ranges are the lasers that can't be seen

Merge all the ranges of lasers that can't be seen from each row.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXR 500000

int L, R;
vector<int> walls[MAXR + 3];

vector<pair<int, int> > mergeSegments(vector<pair<int, int> > segments) {
  vector<pair<int, int> > result;

  if (segments.empty()) {
    return result;
  }

  sort(segments.begin(), segments.end());

  int currentL = segments[0].first, currentR = segments[0].second;
  for (auto [left, right]: segments) {
    if (left > currentR + 1) {
      result.push_back({currentL, currentR});
      currentL = left;
      currentR = right;
    } else {
      currentR = max(currentR, right);
    }
  }

  result.push_back({currentL, currentR});

  return result;
}

vector<pair<int, int> > getBadRangesFromRow(int row) {
  vector<pair<int, int> > goodRanges;

  int sumLength = 0;
  for (auto length: walls[row]) {
    sumLength += length;
  }

  int prefixSum = 0;
  for (auto length: walls[row]) {
    if (prefixSum + (sumLength - prefixSum) < L) {
      goodRanges.push_back({prefixSum + 1, L - (sumLength - prefixSum)});
    }
    prefixSum += length;
  }

  if (prefixSum < L) {
    goodRanges.push_back({prefixSum + 1, L});
  }

  goodRanges = mergeSegments(goodRanges);

  vector<pair<int, int> > badRanges;
  if (goodRanges.empty()) {
    badRanges.push_back({1, L});
  } else {
    for (int i = 1; i < goodRanges.size(); i++) {
      if (goodRanges[i].first > goodRanges[i - 1].second + 1) {
        badRanges.push_back({goodRanges[i - 1].second + 1, goodRanges[i].first - 1});
      }
    }
  }

  return badRanges;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  cin >> L >> R;
  for (int i = 1; i <= R; i++) {
    int X, width;

    cin >> X;
    for (int j = 1; j <= X; j++) {
      cin >> width;
      walls[i].push_back(width);
    }
  }

  vector<pair<int, int> > allBadRanges;
  for (int r = 1; r <= R; r++) {
    vector<pair<int, int> > badRanges = getBadRangesFromRow(r);
    for (auto badRange: badRanges) {
      allBadRanges.push_back(badRange);
    }
  }

  allBadRanges = mergeSegments(allBadRanges);

  int sumOfBadRangesLength = 0;
  for (auto range: allBadRanges) {
    sumOfBadRangesLength += (range.second - range.first + 1);
  }

  cout << sumOfBadRangesLength << endl;
}
