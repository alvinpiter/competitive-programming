#include<bits/stdc++.h>
using namespace std;
#define MAXV 1000000

vector<int> primes;

void generatePrimes() {
    bitset<1001> bs; bs.set();
    for (int i = 2; i <= 1000; i++) {
        if (bs[i]) {
            primes.push_back(i);
            for (int j = i; j <= 1000; j += i)
                bs[j] = 0;
        }
    }
}

int N, counterPrime[1000 + 3], answer;

int expo(int b, int p) {
    if (p == 0)
        return 1;
    else
        return b * expo(b, p - 1);
}

int main() {
    generatePrimes();

    scanf("%d", &N);

    memset(counterPrime, 0, sizeof(counterPrime));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int number;
            scanf("%d", &number);

            if (number == -1)
                continue;

            for (int k = 0; k < primes.size(); k++) {
                while (number % primes[k] == 0) {
                    counterPrime[primes[k]] += 1;
                    number /= primes[k];
                }
            }
        }
    }

    answer = 1;
    for (int i = 0; i < primes.size(); i++) {
        int p = primes[i];
        if (counterPrime[p] % N != 0) {
            int rem = (counterPrime[p]/N + 1)*N - counterPrime[p];
            answer *= expo(p, rem);
        }
    }

    printf("%d\n", answer);
}
