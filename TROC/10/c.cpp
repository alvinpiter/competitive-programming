#include<bits/stdc++.h>
using namespace std;

int triArea(int n) {
    return (n * n + n)/2;
}

int main() {
    int A, B, C, D, E, F;

    cin >> A >> B >> C >> D >> E >> F;

    int largeSize = (F - 1) + A + (B - 1);
    int small1Size = (F - 1);
    int small2Size = (B - 1);
    int small3Size = (D - 1);

    cout << triArea(largeSize) - triArea(small1Size) - triArea(small2Size) - triArea(small3Size) << endl;
}
