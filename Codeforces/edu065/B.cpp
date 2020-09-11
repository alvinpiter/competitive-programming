#include<bits/stdc++.h>
using namespace std;

int ask(int i, int j) {
    cout << "? " << i << " " << j << endl;
    cout.flush();

    int response;
    cin >> response;

    return response;
}

void answer(vector<int> ans) {
    cout << "!";
    for (auto a: ans)
        cout << " " << a;
    cout << endl;

    cout.flush();
}

int numbers[] = {4, 8, 15, 16, 23, 42};

int main() {
    vector<int> ans;

    for (int i = 0; i < 6; i++)
        ans.push_back(numbers[i]);

    int mul01 = ask(1, 2);
    int mul23 = ask(3, 4);
    int mul12 = ask(2, 3);
    int mul04 = ask(1, 5);

    do {
        bool valid = true;
        if (ans[0] * ans[1] != mul01) valid = false;
        if (ans[2] * ans[3] != mul23) valid = false;
        if (ans[1] * ans[2] != mul12) valid = false;
        if (ans[0] * ans[4] != mul04) valid = false;

        if (valid) {
            answer(ans);
            break;
        }
    } while (next_permutation(ans.begin(), ans.end()));
}
