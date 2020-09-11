#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int N, cnt[10][10];
LL answer;

int main() {
    cin >> N;

    for (int i = 1; i <= N; i++) {
        int number = i;

        int lastDigit = number%10;

        while (number >= 10) number /= 10;

        int firstDigit = number;

        cnt[firstDigit][lastDigit] += 1;
    }

    answer = 0;
    for (int f = 1; f <= 9; f++) {
        for (int s = 1; s <= 9; s++) {
            answer += ((LL) cnt[f][s] * cnt[s][f]);
        }
    }

    cout << answer << endl;
}
