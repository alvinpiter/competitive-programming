#include<bits/stdc++.h>
using namespace std;

int n, m, k, dummy;
string answer;

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= 2 * k; i++) {
        cin >> dummy >> dummy;
    }

    answer = "";

    //Left m - 1 times
    for (int i = 1; i <= m - 1; i++)
        answer += "L";

    //Up n - 1 times
    for (int i = 1; i <= n - 1; i++)
        answer += "U";

    //Zigzag
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            for (int j = 1; j <= m - 1; j++)
                answer += "R";

            if (i != n)
                answer += "D";
        } else {
            for (int j = 1; j <= m - 1; j++)
                answer += "L";

            if (i != n)
                answer += "D";
        }
    }

    cout << answer.length() << endl;
    cout << answer << endl;
}
