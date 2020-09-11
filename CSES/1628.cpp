#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, x;
vector<int> firstHalf, secondHalf;
vector<LL> firstSum, secondSum;
LL answer;

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 0; i < n; i++) {
        int number;
        scanf("%d", &number);

        if (i < n/2)
            firstHalf.push_back(number);
        else
            secondHalf.push_back(number);
    }

    int szFirst = (int) firstHalf.size();
    for (int mask = 0; mask < (1 << szFirst); mask++) {
        LL sum = 0;
        for (int i = 0; i < szFirst; i++) {
            if (mask & (1 << i))
                sum += firstHalf[i];
        }

        firstSum.push_back(sum);
    }

    int szSecond = (int) secondHalf.size();
    for (int mask = 0; mask < (1 << szSecond); mask++) {
        LL sum = 0;
        for (int i = 0; i < szSecond; i++) {
            if (mask & (1 << i))
                sum += secondHalf[i];
        }

        secondSum.push_back(sum);
    }

    sort(secondSum.begin(), secondSum.end());

    answer = 0;
    for (auto f: firstSum) {
        int lb = lower_bound(secondSum.begin(), secondSum.end(), x - f) - secondSum.begin();
        int ub = upper_bound(secondSum.begin(), secondSum.end(), x - f) - secondSum.begin();

        if (secondSum[lb] == x - f)
            answer += (ub - lb);
    }

    printf("%lld\n", answer);
}
