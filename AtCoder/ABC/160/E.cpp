#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int X, Y, A, B, C, num;
vector<int> p;
vector<pair<int, int> > others;

int main() {
    cin >> X >> Y >> A >> B >> C;

    for (int i = 0; i < A; i++) {
        cin >> num;
        p.push_back(num);
    }

    for (int i = 0; i < B; i++) {
        cin >> num;
        others.push_back({num, 0});
    }

    for (int i = 0; i < C; i++) {
        cin >> num;
        others.push_back({num, 1});
    }

    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());

    sort(others.begin(), others.end());
    reverse(others.begin(), others.end());

    LL currentSumRed = 0;
    for (int i = 0; i < X; i++)
        currentSumRed += p[i];

    LL currentSumGreen = 0;
    for (int i = 0; i < Y; i++)
        currentSumGreen += others[i].first;

    int ptr1; //points to other color
    int ptr2 = Y - 1;

    for (int i = 0; i < others.size(); i++) {
        if (others[i].second == 1) {
            ptr1 = i;
            break;
        }
    }

    LL best = currentSumRed + currentSumGreen;
    for (int i = X - 1; i >= 0; i--) {
        currentSumRed -= p[i];
        currentSumRed += others[ptr1].first;

        if (ptr1 <= ptr2) {
            ptr2 += 1;

            currentSumGreen -= others[ptr1].first;
            currentSumGreen += others[ptr2].first;
        }

        ptr1 += 1;
        while (ptr1 < others.size() && others[ptr1].second != 1) ptr1 += 1;

        best = max(best, currentSumRed + currentSumGreen);
    }

    cout << best << endl;
}
