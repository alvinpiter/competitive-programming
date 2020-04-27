#include<bits/stdc++.h>
using namespace std;

/*
Observe the first 2 characters and the last 2 characters. They must share at least one character.
Because we can convert 4 (2 from prefix and 2 from suffix) to 2 characters, palindrome with length <= |s|/2 always exist.
*/

int main() {
    char s[1000003];

    scanf("%s", s);

    int l = 0, r = strlen(s) - 1;

    vector<char> prefix;
    vector<char> suffix;
    while (l + 1 < r - 1) {
        if (s[l] == s[r - 1] || s[l] == s[r]) {
            prefix.push_back(s[l]);
            suffix.push_back(s[l]);
        } else {
            prefix.push_back(s[l + 1]);
            suffix.push_back(s[l + 1]);
        }

        l += 2;
        r -= 2;
    }

    if (l < r)
        prefix.push_back(s[l + 1]);

    for (int i = 0; i < (int) prefix.size(); i++) printf("%c", prefix[i]);
    for (int i = (int) suffix.size() - 1; i >= 0; i--) printf("%c", suffix[i]);
    printf("\n");
}
