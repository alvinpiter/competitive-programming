#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL a, result;
    string b;
    int intb;

    cin >> a >> b;

    intb = 0;
    for (int i = 0; i < b.length(); i++) {
        if (b[i] != '.')
            intb = 10*intb + (b[i] - '0');
    }

    result = a * intb;

    cout << result/100 << endl;
}
