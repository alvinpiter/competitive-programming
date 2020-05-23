#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b, answer;

    cin >> n >> a >> b;

    answer = 0;

    //brute force on number of plates that contains first cake
    for (int first = 1; first < n; first++) {
        if (first > a || n - first > b)
            continue;

        int cntA = a/first;
        int cntB = b/(n - first);

        answer = max(answer, min(cntA, cntB));
    }

    cout << answer << endl;
}
