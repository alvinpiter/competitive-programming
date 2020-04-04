#include<bits/stdc++.h>
using namespace std;
#define LL long long int

bool simulate(LL n, LL k) {
    while (n >= k) {
        if (n%k == 0)
            n = n/k;
        else
            n = n%k;
    }

    return (n == 1);
}

int main() {
    LL N;
    set<LL> candidate;

    cin >> N;

    if (N == 2) {
        cout << 1 << endl;
        return 0;
    }

    for (LL div = 2; div * div <= N; div++) {
        if (N % div != 0) continue;

        if (simulate(N, div)) candidate.insert(div);
        if (simulate(N, N/div)) candidate.insert(N/div);
    }

    for (LL div = 2; div * div <= N - 1; div++) {
        if ((N - 1) % div != 0) continue;

        if (simulate(N, div)) candidate.insert(div);
        if (simulate(N, (N - 1)/div)) candidate.insert((N - 1)/div);
    }

    candidate.insert(N);
    candidate.insert(N - 1);

    cout << candidate.size() << endl;
}
