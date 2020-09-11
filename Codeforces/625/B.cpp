#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n;
map<int, LL> sum;
LL answer;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;

        int diff = b - i;
        if (sum.find(diff) == sum.end())
            sum[diff] = b;
        else
            sum[diff] += b;
    }

    answer = 0;
    for (auto p: sum) {
        answer = max(answer, p.second);
    }

    cout << answer << endl;
}
