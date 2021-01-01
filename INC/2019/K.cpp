#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, numOdd, numEven, answer;

    cin >> n;

    numOdd = numEven = 0;
    for (int i = 1; i <= n; i++) {
        int number;
        cin >> number;

        if (number % 2 == 0) {
            numEven += 1;
        } else {
            numOdd += 1;
        }
    }

    answer = 0;

    //pair the evens with the odds
    int paired = min(numEven, numOdd);
    numEven -= paired;
    numOdd -= paired;
    answer += paired;

    //pair the odds
    answer += numOdd/2;

    cout << answer << endl;
}
