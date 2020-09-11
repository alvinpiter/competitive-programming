#include<bits/stdc++.h>
using namespace std;

int N, minPrefixWithRem[7], prefixRem, answer;

int main() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    cin >> N;

    memset(minPrefixWithRem, -1, sizeof(minPrefixWithRem));

    minPrefixWithRem[0] = 0;
    prefixRem = 0;
    answer = 0;
    for (int i = 1; i <= N; i++) {
        int num;
        cin >> num;

        prefixRem = (prefixRem + num)%7;
        if (minPrefixWithRem[prefixRem] != -1) {
            answer = max(answer, i - minPrefixWithRem[prefixRem]);
        } else {
            minPrefixWithRem[prefixRem] = i;
        }
    }

    cout << answer << endl;
}
