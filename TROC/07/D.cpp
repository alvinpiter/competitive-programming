#include<bits/stdc++.h>
using namespace std;

int N;
vector<int> v, v1, v2, v3;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;

        v.push_back(number);
    }

    //Make sure consecutive elements are different
    v1.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (v[i] != v[i - 1])
            v1.push_back(v[i]);
    }

    //Make sure longest increasing subarray is at most 2
    v2.push_back(v1[0]);
    for (int i = 1; i < v1.size(); i++) {
        if (i == v1.size() - 1 || !(v1[i - 1] < v1[i] && v1[i] < v1[i + 1]))
            v2.push_back(v1[i]);
    }

    //Make sure longest decreasing subarray is at most 2
    v3.push_back(v2[0]);
    for (int i = 1; i < v2.size(); i++) {
        if (i == v2.size() - 1 || !(v2[i - 1] > v2[i] && v2[i] > v2[i + 1]))
            v3.push_back(v2[i]);
    }

    cout << v3.size() << endl;
    for (int i = 0; i < v3.size(); i++) {
        if (i > 0)
            cout << " ";

        cout << v3[i];
    }
    cout << endl;
}
