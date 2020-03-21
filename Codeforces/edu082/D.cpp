#include<bits/stdc++.h>
using namespace std;
#define MAXLG 60
#define LL long long int

int getLg(int num) {
    int result = 0;
    while (num%2 == 0) {
        result += 1;
        num /= 2;
    }

    return result;
}

int main() {
    int T, M, counter[MAXLG + 3]; //counter[lg] = how many boxes with size 2^lg
    LL N;

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%lld%d", &N, &M);

        memset(counter, 0, sizeof(counter));
        for (int i = 1; i <= M; i++) {
            int a;
            scanf("%d", &a);

            counter[getLg(a)] += 1;
        }

        bool valid = true;
        int answer = 0;
        int ptr = 0;
        for (int i = 0; i <= MAXLG; i++) {
            if (N & (1LL << i)) {
                //merge all smaller boxes
                while (ptr < i) {
                    counter[ptr + 1] += counter[ptr]/2;
                    counter[ptr] %= 2;
                    ptr += 1;
                }

                if (counter[i] == 0) {
                    //if no boxes is available, we need to divide larger boxes
                    int idx;
                    for (idx = i; idx <= MAXLG; idx++) {
                        if (counter[idx] > 0)
                            break;
                    }

                    if (idx == MAXLG + 1) {
                        //no larger boxes
                        valid = false;
                        break;
                    } else {
                        while (idx > i) {
                            answer += 1;
                            counter[idx] -= 1;
                            counter[idx - 1] += 2;

                            idx -= 1;
                        }

                        counter[i] -= 1;
                    }
                } else {
                    //There is a box available, use it
                    counter[i] -= 1;
                }
            }
        }

        if (valid)
            printf("%d\n", answer);
        else
            printf("-1\n");
    }
}
