#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
First of all, we will find smallest index i such that suffix i..N will be increasing.
The minimal number of moves will be i - 1.
Proof:
Because i is minimal, that means number at i - 1 is larger than number at i.
We need to at least send number at i-1 to its correct position, hence the answer is i - 1.

To construct the answer, we need to know how many numbers lower than current number that
is already "in-position". "in-position" here means that it already belongs to the increasing
suffix. We can maintain "in-position" numbers using BIT.
*/

int N, p[MAXN + 3], bit[MAXN + 3];
vector<int> answer;

void update(int idx, int val) {
    while (idx <= N) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);

    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &p[i]);

    //make sure suffix idx..N is increasing
    int idx = N - 1;
    while (idx > 1 && p[idx] < p[idx + 1])
        idx -= 1;

    idx += 1;

    memset(bit, 0, sizeof(bit));

    //insert all in-position number to bit
    for (int i = idx; i <= N; i++)
        update(p[i], 1);

    //process all out-position number
    for (int i = 1; i < idx; i++) {
        answer.push_back((idx - i - 1) + query(p[i] - 1));
        update(p[i], 1);
    }

    int sz = (int) answer.size();

    printf("%d\n", sz);
    for (int i = 0; i < sz; i++) {
        printf("%d", answer[i]);
        if (i == sz - 1)
            printf("\n");
        else
            printf(" ");
    }
}
