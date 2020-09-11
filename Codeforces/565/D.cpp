#include<bits/stdc++.h>
using namespace std;
#define MAX 2760000

/*
Observation: Largest non prime number must belong to a. So we process non prime number from largest one.
Observation: If a is prime, then p(a) > a. So we need to process prime numbers from smallest one.
*/

int largestDivisor[MAX + 3];
bool isPrime[MAX + 3];
vector<int> primes;

int n, cnt[MAX + 3];
vector<int> p, np; //primes, nonPrimes

int main() {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= MAX; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 1; i <= MAX; i++) {
        for (int j = 2 * i; j <= MAX; j += i)
            largestDivisor[j] = i;
    }

    scanf("%d", &n);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < 2 * n; i++) {
        int b;
        scanf("%d", &b);

        cnt[b] += 1;

        if (isPrime[b]) {
            p.push_back(b);
        } else {
            np.push_back(b);
        }
    }

    sort(p.begin(), p.end());

    sort(np.begin(), np.end());
    reverse(np.begin(), np.end());

    vector<int> answer;
    for (auto num: np) {
        if (cnt[num] == 0) continue;

        answer.push_back(num);
        cnt[num] -= 1;
        cnt[largestDivisor[num]] -= 1;
    }

    for (auto num: p) {
        if (cnt[num] == 0) continue;

        answer.push_back(num);
        cnt[num] -= 1;
        cnt[primes[num - 1]] -= 1;
    }

    for (auto a: answer)
        printf("%d ", a);
    printf("\n");
}
