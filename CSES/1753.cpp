#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
#define DEBUG true

/*
f[i] = index j (j < i) such that s[0..j-1] is proper prefix and proper suffix of s[0..i - 1]

The base case if f[0] = -1
We need a pointer that points to last failure value, let's name it prevF.
*/
int countOccurences(string text, string pattern) {
    int f[MAXN + 3], prevF;

    //Initialize failure function
    f[0] = -1;
    prevF = f[0];
    for (int i = 1; i <= pattern.length(); i++) {
        while (prevF != -1 && pattern[i - 1] != pattern[prevF])
            prevF = f[prevF];

        f[i] = prevF + 1;
        prevF = f[i];
    }

    //Count occurences of pattern in text using KMP algorithm
    int count = 0;
    int toMatchIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        while (toMatchIndex != -1 && text[i] != pattern[toMatchIndex])
            toMatchIndex = f[toMatchIndex];

        toMatchIndex += 1;

        if (toMatchIndex == pattern.length()) {
            count += 1;
            toMatchIndex = f[toMatchIndex];
        }
    }

    return count;
}

int main() {
    string text, pattern;

    cin >> text >> pattern;

    cout << countOccurences(text, pattern) << endl;
}
