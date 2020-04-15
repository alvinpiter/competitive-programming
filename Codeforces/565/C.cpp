#include<bits/stdc++.h>
using namespace std;

int numbers[] = {4, 8, 15, 16, 23, 42};

int id(int num) {
    for (int i = 0; i < 6; i++) {
        if (numbers[i] == num)
            return i;
    }
}

int main() {
    int n, answer;
    vector<int> pos[6];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        pos[id(a)].push_back(i);
    }

    //put smallest index at back
    for (int i = 0; i < 6; i++)
        reverse(pos[i].begin(), pos[i].end());

    answer = 0;

    while (true) {
        if (pos[0].empty()) break;

        bool can = true;
        int last = pos[0].back();

        for (int i = 1; i < 6; i++) {
            while (!pos[i].empty() && pos[i].back() < last) {
                answer += 1;
                pos[i].pop_back();
            }

            if (pos[i].empty()) {
                can = false;
                break;
            }

            last = pos[i].back();
        }

        if (can) {
            for (int i = 0; i < 6; i++)
                pos[i].pop_back();
        } else {
            break;
        }
    }

    for (int i = 0; i < 6; i++)
        answer += (int) pos[i].size();

    printf("%d\n", answer);
}
