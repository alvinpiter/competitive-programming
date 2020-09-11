#include<bits/stdc++.h>
using namespace std;
#define LL long long int

vector<int> divisors;
vector<LL> possibilities;
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103};

//Find all possible factorization of n
void factorize(int n) {
    if (n == 1) {
        vector<int> temp(divisors);

        sort(temp.begin(), temp.end(), greater<int>());

        LL number = 1;
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] > 64)
                return;

            for (int rep = 1; rep <= temp[i] - 1; rep++)
                number *= primes[i];
        }

        possibilities.push_back(number);

        return;
    }

    for (int div = 2; div <= n; div++) {
        if (n % div == 0) {
            divisors.push_back(div);
            factorize(n/div);
            divisors.pop_back();
        }
    }
}

LL solve(int n) {
    divisors.clear();
    possibilities.clear();

    factorize(n);

    LL answer = 8e18;
    for (auto p: possibilities) {
        if (p > 0)
            answer = min(answer, p);
    }

    return answer;
}

int main() {
    // for (int i = 1; i <= 1000; i++) {
    //     cout << i << " " << solve(i) << endl;
    // }

    int n;
    cin >> n;

    cout << solve(n) << endl;
}
