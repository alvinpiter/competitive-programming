#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    char grid[503][503];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cin >> grid[i][j];
    }

    int answer = 0;
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < n; j++) {
            if (grid[i][j] == 'X' && grid[i - 1][j - 1] == 'X' && grid[i - 1][j + 1] == 'X' && grid[i + 1][j - 1] == 'X' && grid[i + 1][j + 1] == 'X')
                answer += 1;
        }
    }

    cout << answer << endl;
}
