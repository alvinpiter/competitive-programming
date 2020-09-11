#include<bits/stdc++.h>
using namespace std;

//how many string of digits with length len and contains numNonZero non-zero digits
int cnt(int len, int numNonZero) {
    if (len == 0) {
        return (numNonZero == 0 ? 1 : 0);
    }

    if (numNonZero < 0 || numNonZero > len)
        return 0;

    if (numNonZero == 0)
        return 1;
    else if (numNonZero == 1)
        return 9 * len;
    else if (numNonZero == 2)
        return 9 * 9 * ((len * len - len)/2);
    else if (numNonZero == 3)
        return 9 * 9 * 9 * (len*(len - 1)*(len - 2))/6;
}

//how many integers below s that contains exactly k non zero digits
int f(string s, int k) {
    int len = (int) s.length();
    int numNonZeroSoFar = 0;

    int answer = 0;
    for (int i = 0; i < len; i++) {
        int currDigit = (int) (s[i] - '0');
        for (int dig = currDigit - 1; dig >= 0; dig--) {
            if (dig == 0)
                answer += cnt(len - i - 1, k - numNonZeroSoFar);
            else
                answer += cnt(len - i - 1, k - numNonZeroSoFar - 1);
        }

        if (currDigit != 0)
            numNonZeroSoFar += 1;
    }

    return answer;
}

int main() {
    string N;
    int K;

    cin >> N >> K;

    int answer = 0;
    answer += f(N, K);

    int numNonZero = 0;
    for (int i = 0; i < N.length(); i++) {
        if (N[i] != '0')
            numNonZero += 1;
    }

    if (numNonZero == K)
        answer += 1;

    cout << answer << endl;
}
