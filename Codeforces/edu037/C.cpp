#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[200003];
    char s[200003];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    scanf("%s", s);

    for (int i = 0; i < n - 1; ) {
        if (s[i] == '0') {
            i += 1;
            continue;
        }

        int j = i;
        while (j < n - 1 && s[j] == '1') j += 1;

        sort(a + i, a + j + 1);

        i = j;
    }

    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
}
