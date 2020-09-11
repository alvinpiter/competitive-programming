#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, A[MAXN + 3], answer;

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    sort(A + 1, A + N + 1);

    answer = 1e9;
    for (int i = 1; i + M - 1 <= N; i++)
        answer = min(answer, A[i + M - 1] - A[i]);

    cout << answer << endl;
}
