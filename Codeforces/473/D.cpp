#include<bits/stdc++.h>
using namespace std;
#define MAX 1500000
#define MAXN 100000

int n, a[MAXN + 3];
bool marked[MAX + 3];

void markSiblings(int num) {
    for (int d = 2; d * d <= num; d++) {
        if (num % d == 0) {
            if (marked[d] == false) {
                for (int m = 2 * d; m <= MAX; m += d)
                    marked[m] = true;
            }

            marked[d] = true;
            while (num % d == 0) num /= d;
        }
    }

    if (num != 1) {
        if (marked[num] == false) {
            for (int m = 2 * num; m <= MAX; m += num)
                marked[m] = true;
        }

        marked[num] = true;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> answer;

    answer.push_back(a[0]);
    markSiblings(a[0]);

    for (int i = 1; i < n; i++) {
        for (int j = a[i]; ; j++) {
            if (marked[j] == false) {
                answer.push_back(j);
                markSiblings(j);

                break;
            }
        }

        if (answer.back() > a[i])
            break;
    }

    int num = 2;
    while (answer.size() < n) {
        while (marked[num])
            num += 1;

        answer.push_back(num);
        markSiblings(num);
    }

    for (auto a: answer)
        cout << a << " ";
    cout << endl;
}
