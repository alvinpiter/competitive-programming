#include<bits/stdc++.h>
using namespace std;

void printBorderLengths(string text) {
    int f[text.length() + 3], prevF;

    f[0] = -1;
    prevF = f[0];
    for (int i = 1; i <= text.length(); i++) {
        while (prevF != -1 && text[i - 1] != text[prevF])
            prevF = f[prevF];

        f[i] = prevF + 1;
        prevF = f[i];
    }

    vector<int> borderLengths;
    int current = text.length();
    while (true) {
        if (f[current] <= 0)
            break;

        borderLengths.push_back(f[current]);
        current = f[current];
    }

    sort(borderLengths.begin(), borderLengths.end());
    for (int i = 0; i < borderLengths.size(); i++) {
        if (i > 0)
            cout << " ";

        cout << borderLengths[i];
    }
    cout << endl;
}

int main() {
    string text;

    cin >> text;

    printBorderLengths(text);
}
