#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

//colorOfChar[i] -> Longest decreasing subsequence ending at character i

int N, colorOfChar[26], colorOfIndex[MAXN + 3];

int main() {
    cin >> N;

    memset(colorOfChar, 0, sizeof(colorOfChar));
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        int charIndex = (c - 'a');

        //Check max decreasing subsequence
        int maxi = 0;
        for (int j = charIndex + 1; j < 26; j++)
            maxi = max(maxi, colorOfChar[j]);

        colorOfIndex[i] = maxi + 1;
        colorOfChar[charIndex] = max(colorOfChar[charIndex], colorOfIndex[i]);
    }

    int maxColor = 0;
    for (int i = 1; i <= N; i++)
        maxColor = max(maxColor, colorOfIndex[i]);

    cout << maxColor << endl;
    for (int i = 1; i <= N; i++)
        cout << colorOfIndex[i] << " ";
    cout << endl;
}
