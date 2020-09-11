#include<bits/stdc++.h>
using namespace std;
#define MAXV 2000000
#define LL long long int

int N, counter[MAXV + 3];

int numDivisibleBy(int x) {
    int result = 0;
    for (int i = x; i <= MAXV; i += x)
        result += counter[i];

    return result;
}

int main() {
    cin >> N;

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= N; i++) {
        int sz;

        cin >> sz;
        counter[sz] += 1;
    }

    LL answer = 0;
    for (int d = 1; d <= MAXV; d++) {
        int num = numDivisibleBy(d);

        if (num != 1)
            answer = max(answer, (LL) num * d);
    }

    cout << answer << endl;
}
