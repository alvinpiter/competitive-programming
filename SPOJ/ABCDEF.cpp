#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, numbers[103];
    vector<int> abc, def;

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> numbers[i];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                abc.push_back(numbers[i] * numbers[j] + numbers[k]);

                if (numbers[i] != 0)
                    def.push_back(numbers[i] * (numbers[j] + numbers[k]));
            }
        }
    }

    map<int, int> counter;
    for (int i = 0; i < abc.size(); i++) {
        if (counter.find(abc[i]) == counter.end()) {
            counter[abc[i]] = 1;
        } else {
            counter[abc[i]] += 1;
        }
    }

    int answer = 0;
    for (int i = 0; i < def.size(); i++) {
        answer += counter[def[i]];
    }

    cout << answer << endl;
}
