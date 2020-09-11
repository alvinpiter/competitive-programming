#include<bits/stdc++.h>
using namespace std;

int id(char c) {
    char chars[] = {'B', 'E', 'S', 'I', 'G', 'O', 'M'};
    for (int i = 0; i < 7; i++) {
        if (chars[i] == c)
            return i;
    }
}

int cnt[7][7]; //cnt[i][j] -> how many values for character i that is congruent to j modulo 7

int mod7(int num) {
    if (num < 0)
        return (abs(num)/7 + (abs(num)%7 == 0 ? 0 : 1))*7 + num;
    else
        return num%7;
}

int main() {
    freopen("bgm.in", "r", stdin);
    freopen("bgm.out", "w", stdout);

    int N, val;
    string s;

    memset(cnt, 0, sizeof(cnt));

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> s >> val;
        cnt[id(s[0])][mod7(val)]++;
    }

    long long int answer = 0;
    for (int b = 0; b < 7; b++) {
        for (int e = 0; e < 7; e++) {
            for (int s = 0; s < 7; s++) {
                for (int i = 0; i < 7; i++) {
                    for (int g = 0; g < 7; g++) {
                        for (int o = 0; o < 7; o++) {
                            for (int m = 0; m < 7; m++) {
                                int res = (b + e + s + s + i + e)*(g + o + e + s)*(m + o + o);
                                if (res%7 == 0) {
                                    answer += (long long int) cnt[0][b] * cnt[1][e] * cnt[2][s] * cnt[3][i] * cnt[4][g] * cnt[5][o] * cnt[6][m];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << answer << endl;
}
