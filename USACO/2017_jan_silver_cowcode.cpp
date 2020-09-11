#include<bits/stdc++.h>
using namespace std;
#define LL long long int

string S;
LL N;

//Find k-th character on the iteration-th string
char find(int iteration, LL k) {
    if (iteration == 0)
        return S[k - 1];

    LL len = (1LL << iteration) * S.length();
    if (k <= len/2)
        return find(iteration - 1, k);
    else if (k == len/2 + 1)
        return find(iteration - 1, len/2);
    else
        return find(iteration - 1, k - len/2 - 1);
}

int main() {
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);

    cin >> S >> N;

    //Find in which iteration our answer will exist
    int iteration = 0;
    while (true) {
        LL sz = (1LL << iteration) * S.length();
        if (sz >= N)
            break;

        iteration += 1;
    }

    cout << find(iteration, N) << endl;
}
