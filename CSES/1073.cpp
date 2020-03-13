#include<bits/stdc++.h>
using namespace std;

int N, K, answer;
multiset<int> tops;

int main() {
    cin >> N;

    answer = 0;
    for (int i = 1; i <= N; i++) {
        cin >> K;

        set<int>::iterator ptr = tops.lower_bound(K + 1);
        if (ptr == tops.end()) {
            answer += 1;
            tops.insert(K);
        } else {
            tops.erase(ptr);
            tops.insert(K);
        }
    }

    cout << answer << endl;
}
