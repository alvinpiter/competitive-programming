#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<pair<int, int> > numbers;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);

        numbers.push_back({num, i + 1});
    }

    sort(numbers.begin(), numbers.end());

    multiset<int> diffSet;
    for (int i = 1; i < n; i++)
        diffSet.insert(numbers[i].first - numbers[i - 1].first);

    for (int i = 0; i < n; i++) {

        bool possible = false;
        if (i == 0) {
            int diff = numbers[i + 1].first - numbers[i].first;
            diffSet.erase(diffSet.find(diff));

            if (diffSet.empty() || *diffSet.begin() == *(--diffSet.end()))
                possible = true;

            diffSet.insert(diff);
        } else if (i == n - 1) {
            int diff = numbers[i].first - numbers[i - 1].first;
            diffSet.erase(diffSet.find(diff));

            if (diffSet.empty() || *diffSet.begin() == *(--diffSet.end()))
                possible = true;

            diffSet.insert(diff);
        } else {
            int prvDiff = numbers[i].first - numbers[i - 1].first;
            int nxtDiff = numbers[i + 1].first - numbers[i].first;
            int newDiff = numbers[i + 1].first - numbers[i - 1].first;

            diffSet.erase(diffSet.find(prvDiff));
            diffSet.erase(diffSet.find(nxtDiff));
            diffSet.insert(newDiff);

            if (diffSet.empty() || *diffSet.begin() == *(--diffSet.end()))
                possible = true;

            diffSet.insert(prvDiff);
            diffSet.insert(nxtDiff);
            diffSet.erase(diffSet.find(newDiff));
        }

        if (possible) {
            printf("%d\n", numbers[i].second);
            return 0;
        }
    }

    printf("-1\n");
}
