#include<bits/stdc++.h>
using namespace std;

int N, arr[2003];

void scramble(int l, int r) {
    if (r - l + 1 <= 2)
        return;

    int swapNeeded = 0;
    for (int i = 0; l + i <= r; i += 2) {
        int currentIndex = l + i;
        int swapLeft = swapNeeded;

        while (swapLeft > 0) {
            swap(arr[currentIndex], arr[currentIndex - 1]);
            currentIndex -= 1;
            swapLeft -= 1;
        }

        swapNeeded += 1;
    }

    int m = (l + r)/2;
    scramble(l, m);
    scramble(m + 1, r);
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        arr[i] = i;

    scramble(1, N);

    for (int i = 1; i <= N; i++)
        cout << arr[i] << endl;
}
