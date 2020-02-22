#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int T, N;
LL M;

LL C3(LL num, LL mod) {
    LL result = ((LL) num * (num - 1))/2;

    if (result%3 == 0) {
        result /= 3;
        result = ((result%M) * (num - 2)%M)%M;

        return result;
    } else {
        result = ((result%M) * ((num - 2)/3)%M)%M;
        return result;
    }
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%lld", &N, &M);

        LL prevNumWays = 2%M;
        int prevNumElements = 3;
        for (int i = 2; i <= N; i++) {
            LL ways1 = C3(prevNumElements + 3, M); //Divide previous elements into 4 bucket (short, sock, shoe)
            LL totalWays = (2*((prevNumWays * ways1)%M))%M;

            prevNumWays = totalWays;
            prevNumElements += 3;
        }

        printf("Case #%d: %lld\n", cases, prevNumWays);
    }
}
