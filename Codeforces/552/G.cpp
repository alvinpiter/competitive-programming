#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXA 10000000
#define MAXN 1000000

/*
For every d, find two smallest number a and b such that a and b is divisible by d.
*/

int n, a[MAXN + 3], maxi;
bool visited[MAXA + 3];
int smallestDivisor[MAXA + 3];
int divisible[MAXA + 3][2]; //divisible[i] -> set of indicies i such that ai is divisible by i
vector<pair<int, int> > factorization;

void factorize(int num) {
    factorization.clear();

    while (num != 1) {
        int d = smallestDivisor[num];

        if (!factorization.empty() && factorization.back().first == d)
            factorization.back().second += 1;
        else
            factorization.push_back({d, 1});

        num /= d;
    }
}

void updateDivisible(int d, int idx) {
    if (divisible[d][0] == -1) {
        divisible[d][0] = idx;
    } else if (divisible[d][1] == -1) {
        if (a[idx] < a[divisible[d][0]]) {
            divisible[d][1] = divisible[d][0];
            divisible[d][0] = idx;
        } else {
            divisible[d][1] = idx;
        }
    } else {
        if (a[idx] < a[divisible[d][0]]) {
            divisible[d][1] = divisible[d][0];
            divisible[d][0] = idx;
        } else if (a[idx] < a[divisible[d][1]]) {
            divisible[d][1] = idx;
        }
    }
}

void traverseDivisor(int pIdx, int divisor, int idx) {
    if (pIdx == factorization.size()) {
        updateDivisible(divisor, idx);
        return;
    }

    traverseDivisor(pIdx + 1, divisor, idx);
    for (int i = 1; i <= factorization[pIdx].second; i++) {
        divisor *= factorization[pIdx].first;
        traverseDivisor(pIdx + 1, divisor, idx);
    }
}

void add(int idx) {
    factorize(a[idx]);
    traverseDivisor(0, 1, idx);
}

int main() {
    scanf("%d", &n);

    maxi = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        maxi = max(maxi, a[i]);
    }

    for (int i = 1; i <= maxi; i++) {
        visited[i] = false;
        smallestDivisor[i] = i;
        divisible[i][0] = divisible[i][1] = -1;
    }

    for (int i = 2; i <= maxi; i++) {
        if (visited[i] == false) {
            visited[i] = true;
            for (LL j = (LL) i * i; j <= maxi; j += i) {
                visited[j] = true;
                smallestDivisor[j] = min(smallestDivisor[j], i);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        add(i);

    LL best = 1e18;
    int ans1, ans2;
    for (int d = 1; d <= maxi; d++) {
        if (divisible[d][1] != -1) {
            int i1 = divisible[d][0];
            int i2 = divisible[d][1];
            LL lcm = (LL) (a[i1]/d)*a[i2];

            if (lcm < best) {
                best = lcm;
                ans1 = i1;
                ans2 = i2;
            }
        }
    }

    printf("%d %d\n", min(ans1, ans2), max(ans1, ans2));
}
