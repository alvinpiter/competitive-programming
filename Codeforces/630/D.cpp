#include<bits/stdc++.h>
using namespace std;
#define MAX (1 << 17)

int main() {
    int k;

    scanf("%d", &k);
    printf("2 3\n");
    printf("%d %d %d\n", MAX + k, MAX, MAX);
    printf("%d %d %d\n", k, MAX + k, k);
}
