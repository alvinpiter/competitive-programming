#include<bits/stdc++.h>
using namespace std;

int main() {
    int N;
    char response[5];
    bool truth;

    scanf("%d", &N);
    scanf("%s", response);

    truth = (response[0] == 'T' ? true : false);
    for (int i = 2; i <= N; i++) {
        scanf("%s", response);
        if (response[0] == 'L')
            truth = !truth;
    }

    if (truth)
        printf("TRUTH\n");
    else
        printf("LIE\n");
}
