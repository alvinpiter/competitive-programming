#include<bits/stdc++.h>
using namespace std;

int n, x;
vector<pair<int, int> > numbers;

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        numbers.push_back({a, i});
    }

    sort(numbers.begin(), numbers.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int lo = j + 1;
            int hi = n - 1;
            int mid;
            int target = x - numbers[i].first - numbers[j].first;

            while (hi >= lo) {
                mid = (lo + hi)/2;
                if (numbers[mid].first < target)
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }

            if (lo < n && numbers[lo].first == target) {
                cout << numbers[i].second << " " << numbers[j].second << " " << numbers[lo].second << endl;
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}
