#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int> answer;

    cin >> n;
    for (int i = 1; i <= n; i += 2)
        answer.push_back(i);

    if (n%2 == 0)
        answer.push_back(n);

    cout << (int) answer.size() << endl;
    for (auto a: answer)
        cout << a << " ";
    cout << endl;
}
