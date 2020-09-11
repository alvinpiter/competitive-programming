#include<bits/stdc++.h>
using namespace std;

int K, N, p[200003];
double maxi, current;

int sum(int n) { return (n * n + n)/2; }

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> p[i];

    current = 0;
    for (int i = 1; i <= K; i++) {
        current += (double) sum(p[i])/p[i];
    }

    maxi = current;

    int ptr = 1;
    for (int i = K + 1; i <= N; i++) {
        current += (double) sum(p[i])/p[i];
        current -= (double) sum(p[ptr])/p[ptr];

        ptr += 1;

        maxi = max(maxi, current);
    }

    printf("%.7f\n", maxi);
}
