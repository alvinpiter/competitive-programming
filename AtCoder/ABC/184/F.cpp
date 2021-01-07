#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

vector<LL> generateSubsetSum(vector<int> numbers) {
    int n = (int) numbers.size();
    vector<LL> result;

    for (int mask = 0; mask < (1 << n); mask++) {
        LL sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += numbers[i];
            }
        }

        result.push_back(sum);
    }

    return result;
}

int main() {
    int N;
    LL T;
    vector<int> firstSet, secondSet;

    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;

        if (i < N/2) {
            firstSet.push_back(number);
        } else {
            secondSet.push_back(number);
        }
    }

    vector<LL> firstSubsetSum = generateSubsetSum(firstSet);
    vector<LL> secondSubsetSum = generateSubsetSum(secondSet);

    LL answer = 0;

    sort(secondSubsetSum.begin(), secondSubsetSum.end());

    for (int i = 0; i < (int) firstSubsetSum.size(); i++) {
        LL firstSum = firstSubsetSum[i];

        if (firstSum > T) {
            continue;
        }

        LL maxi = T - firstSum;
        int ub = upper_bound(secondSubsetSum.begin(), secondSubsetSum.end(), maxi) - secondSubsetSum.begin();

        if (ub == 0) {
            answer = max(answer, firstSum);
        } else {
            answer = max(answer, firstSum + secondSubsetSum[ub - 1]);
        }
    }

    cout << answer << endl;
}
