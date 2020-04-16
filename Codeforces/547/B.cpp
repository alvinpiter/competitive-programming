#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[200003], cnt, answer;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    cnt = answer = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (a[i%n] == 0)
            cnt = 0;
        else {
            cnt += 1;
            answer = max(answer, cnt);
        }
    }

    printf("%d\n", min(answer, n));
}
