/*
Calculating the minimal total price:
* Purchase all item type which is sold cheaper at store A. If the number of such item
  is >= X, then purchase the rest from store B and we are done.
* Otherwise, assume i1, i2, i3, .. ik are indices of the item which are sold cheaper at
  store B. We will pick a subset of this item types and buy them from store A.
  Let sumOfLeftOverB = sum(B[i]), i = {i1, i2, .., ik}, i.e it is as if we buy the rest
  from store B.

  If we purchase the ij-th item from store A instead of store B, it will decrease the total price
  by B[ij] - A[ij]. Hence the optimal strategy is to greedily pick the items that yield maximal
  decrease in the total price.

Calculating the maximal total price can be done in almost similar way.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL getMinTotalPrice(vector<int> A, vector<int> B, int X) {
  int N = A.size();
  vector<int> deltas;

  LL result = 0;
  LL sumLeftOverB = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] <= B[i]) {
      result += A[i];
      X -= 1;
    } else {
      deltas.push_back(B[i] - A[i]);
      sumLeftOverB += B[i];
    }
  }

  sort(deltas.begin(), deltas.end(), greater<int>());

  for (int i = 0; i < X; i++) {
    sumLeftOverB -= deltas[i];
  }

  result += sumLeftOverB;

  return result;
}

LL getMaxTotalPrice(vector<int> A, vector<int> B, int X) {
  for (int i = 0; i < A.size(); i++) A[i] *= -1;
  for (int i = 0; i < B.size(); i++) B[i] *= -1;

  return -1 * getMinTotalPrice(A, B, X);
}

int main() {
  int N, X;
  cin >> N >> X;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  cout << getMaxTotalPrice(A, B, X) - getMinTotalPrice(A, B, X) << endl;
}
