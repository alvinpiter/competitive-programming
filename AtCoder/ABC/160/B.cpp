#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X;
    cin >> X;

    cout << (X/500)*1000 + ((X%500)/5)*5 << endl;
}
