#include<bits/stdc++.h>
using namespace std;
#define LL long long int

//Observation: The answer is either string with length 1 or string with length 2

string s;
int n, cntOne[26];
LL ans;
map<string, LL> cntTwo;

int main() {
    cin >> s;

    n = (int) s.length();

    memset(cntOne, 0, sizeof(cntOne));

    ans = 0;
    for (int i = 0; i < n; i++) {
        for (char prv = 'a'; prv <= 'z'; prv++) {
            string temp = "";
            temp += prv;
            temp += s[i];

            cntTwo[temp] += cntOne[prv - 'a'];
            ans = max(ans, cntTwo[temp]);
        }

        cntOne[s[i] - 'a'] += 1;
        ans = max(ans, (LL) cntOne[s[i] - 'a']);
    }

    cout << ans << endl;
}
