#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int n, h[MAXN + 3], sorted[MAXN + 3];

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        sorted[i] = h[i];
    }

    sort(sorted + 1, sorted + n + 1);

    sorted[0] = 0; //dummy

    int ptr = 0;
    int answer = 0;

    for (int i = 1; i <= n; i++) {
        if (h[i] == sorted[ptr]) {
            ptr += 1;
        } else if (h[i] > sorted[ptr]) {
            while (sorted[ptr] < h[i])
                ptr += 1;
        }

        if (i == ptr) {
            answer += 1;
        }
    }

    printf("%d\n", answer);
}
