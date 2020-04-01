#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, K, prefixSum[MAXN + 3], ptr;
map<int, int> counter;
LL answer;

int mod(int a, int b) {
    if (a >= 0)
        return a%b;
    else {
        int absa = abs(a);
        return (absa/b + (absa%b == 0 ? 0 : 1))*b + a;
    }
}

int main() {
    cin >> N >> K;

    prefixSum[0] = 0;
    for (int i = 1; i <= N; i++) {
        int A;
        cin >> A;

        prefixSum[i] = (prefixSum[i - 1] + A)%K;
    }

    int ptr = 0;
    counter[0] = 1;
    answer = 0;

    for (int i = 1; i <= N; i++) {
        while (i - ptr + 1 > K) {
            counter[mod(prefixSum[ptr] - ptr, K)] -= 1;
            ptr += 1;
        }

        int target = mod(prefixSum[i] - i, K);
        if (counter.find(target) == counter.end()) {
            counter[target] = 1;
        } else {
            answer += counter[target];
            counter[target] += 1;
        }
    }

    cout << answer << endl;
}
