#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXS 1000000

int A, B, C, D, cnt[MAXS + 3]; //cnt[i] -> how many pairs of (x, y) such that x + y = i
LL sumCnt[MAXS + 3];

int main() {
    cin >> A >> B >> C >> D;

    memset(cnt, 0, sizeof(cnt));
    for (int x = A; x <= B; x++) {
        cnt[x + B] += 1;
        cnt[x + C + 1] -= 1;
    }

    for (int i = 1; i <= MAXS; i++)
        cnt[i] += cnt[i - 1];

    sumCnt[0] = 0;
    for (int i = 1; i <= MAXS; i++)
        sumCnt[i] = sumCnt[i - 1] + cnt[i];

    LL answer = 0;
    for (int z = C; z <= D; z++)
        answer += sumCnt[MAXS] - sumCnt[z];

    cout << answer << endl;
}
