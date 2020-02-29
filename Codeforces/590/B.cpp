#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define OFFSET 200000

int n, k, id;
int top, bottom, arr[MAXN + 3];
set<int> ids;

int sz() {
    return bottom - top + 1;
}

void insert(int num) {
    if (ids.find(num) != ids.end())
        return;

    if (sz() == k) {
        ids.erase(arr[bottom + OFFSET]);
        bottom -= 1;
    }

    ids.insert(num);
    top -= 1;
    arr[top + OFFSET] = num;
}


int main() {
    cin >> n >> k;

    top = 1;
    bottom = 0;
    for (int i = 1; i <= n; i++) {
        int number;
        cin >> number;

        insert(number);
    }

    cout << sz() << endl;
    for (int i = top; i <= bottom; i++)
        cout << arr[i + OFFSET] << " ";
    cout << endl;
}
