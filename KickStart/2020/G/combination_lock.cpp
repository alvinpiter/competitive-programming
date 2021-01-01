#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

int T, W, N;
LL numbers[100003], prefixSum[100003], answer;

LL getSum(int i, int j) {
    if (i > j) {
        return 0;
    }

    return prefixSum[j] - (i > 0 ? prefixSum[i - 1] : 0);
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> W >> N;

        for (int i = 0; i < W; i++) {
            cin >> numbers[i];
        }

        sort(numbers, numbers + W);

        prefixSum[0] = numbers[0];
        for (int i = 1; i < W; i++) {
            prefixSum[i] = prefixSum[i - 1] + numbers[i];
        }

        answer = (1LL << 60);
        for (int j = 0; j < W; j++) {
            //Find the last lock to the right that will be turned left.
            int k = (upper_bound(numbers, numbers + W, numbers[j] + N/2) - numbers) - 1;

            //Find the first lock to the left that will be turned right.
            int i = (lower_bound(numbers, numbers + W, numbers[j] - N/2) - numbers);

            LL cost = 0;

            //Calculating cost for j..k
            cost += getSum(j, k) - numbers[j] * (k - j + 1);

            //Calculating cost for (k + 1)..(W - 1)
            cost += (numbers[j] + N) * ((W - 1) - (k + 1) + 1) - getSum(k + 1, W - 1);

            //Calculating cost for i..(j - 1)
            cost += numbers[j] * ((j - 1) - i + 1) - getSum(i, j - 1);

            //calculating cost for 0..(i - 1)
            cost += (-numbers[j] + N) * ((i - 1) - 0 + 1) + getSum(0, i - 1);


            answer = min(answer, cost);
        }

        cout << "Case #" << cases << ": " << answer << endl;
    }
}

/*
There must be at least one wheel that does not change value

How to solve:
* Sort the numbers.
* Assume we want all the lock to show X.
* For all locks with value Y >= X, the number of turns needed is min(Y - X, N - (Y - X)). So:
    * We will turn it to the left if Y <= floor(N/2) + X.
    * Else we will turn it to the right

* For all locks with value Y < X:
    * We will turn it to the right if Y >= X - floor(N/2).
    * Else we will turn it to the left

*/
