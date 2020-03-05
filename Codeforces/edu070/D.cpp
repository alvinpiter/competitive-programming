#include<bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        int num3 = 0;
        while ((num3 * num3 + num3)/2 <= n)
            num3 += 1;

        int extra7 = n - (num3 * num3 - num3)/2;

        string answer = "";
        answer += "133";
        for (int i = 0; i < extra7; i++)
            answer += "7";
        for (int i = 0; i < num3 - 2; i++)
            answer += "3";
        answer += "7";

        cout << answer << endl;
    }
}
