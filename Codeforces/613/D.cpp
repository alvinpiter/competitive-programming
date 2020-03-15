#include<bits/stdc++.h>
using namespace std;
#define MAXLG 30;

int n;

int minimize(vector<int>& numbers, int bitIdx) {
    if (bitIdx == -1) return 0;

    vector<int> setOff, setOn;
    for (auto number: numbers) {
        if (number & (1 << bitIdx))
            setOn.push_back(number);
        else
            setOff.push_back(number);
    }

    if (setOff.empty()) return minimize(setOn, bitIdx - 1);
    if (setOn.empty()) return minimize(setOff, bitIdx - 1);

    return (1 << bitIdx) + min(minimize(setOff, bitIdx - 1), minimize(setOn, bitIdx - 1));
}

int main() {
    scanf("%d", &n);

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int number;
        scanf("%d", &number);

        a.push_back(number);
    }

    printf("%d\n", minimize(a, 30));
}
