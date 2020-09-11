#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, answer;
    string a, b;

    cin >> n >> a >> b;

    answer = 0;
    int l = 0, r = n - 1;

    int cnt[26];
    vector<int> sortedCnt;
    while (r > l) {
        memset(cnt, 0, sizeof(cnt));
        cnt[a[l] - 'a'] += 1;
        cnt[a[r] - 'a'] += 1;
        cnt[b[l] - 'a'] += 1;
        cnt[b[r] - 'a'] += 1;

        sortedCnt.clear();
        for (int i = 0; i < 26; i++) {
            if (cnt[i] > 0)
                sortedCnt.push_back(cnt[i]);
        }

        if (sortedCnt.size() == 2) {
            //Case 1,3 or 2,2

            if (sortedCnt[0] != 2)
                answer += 1;
        } else if (sortedCnt.size() == 3) {
            //Case 1,1,2

            if (a[l] == a[r])
                answer += 2;
            else
                answer += 1;
        } else if (sortedCnt.size() == 4) {
            //Case 1,1,1,1

            answer += 2;
        }

        l += 1;
        r -= 1;
    }

    if (l == r && a[l] != b[r])
        answer += 1;

    cout << answer << endl;
}
