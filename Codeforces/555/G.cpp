#include<bits/stdc++.h>
using namespace std;
#define MAXN 200
#define DEBUG true

int N, M, a[MAXN + 3][MAXN + 3];

//Returns a list of integers that denotes whether particular columns need to be toggled if we want the first c charactes in first row to be 0 and the rest to be 1.
vector<int> getColumnToggleStatus(int c) {
    vector<int> toggleStatus(M, 0);

    for (int j = 1; j <= M; j++) {
        if (j <= c && a[1][j] != 0) toggleStatus[j - 1] = 1;
        if (j > c  && a[1][j] != 1) toggleStatus[j - 1] = 1;
    }

    return toggleStatus;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            cin >> a[i][j];
    }

    //Make the first c column becomes 0 and the rest becomes 1
    for (int c = 0; c < M; c++) {
        vector<int> toggledColumns = getColumnToggleStatus(c);
        vector<int> toggledRows(N, 0);

        bool valid = true;

        for (int i = 2; i <= N; i++) {
            int paritySum = 0;
            for (int j = 1; j <= M; j++)
                paritySum += (a[i][j] + toggledColumns[j - 1])%2;

            if (paritySum != 0 && paritySum != M) {
                valid = false;
                break;
            }

            if (paritySum == 0) {
                toggledRows[i - 1] = 1;
            }
        }

        if (valid) {
            cout << "YES\n";
            for (auto t: toggledRows) cout << t;
            cout << endl;
            for (auto t: toggledColumns) cout << t;
            cout << endl;

            return 0;
        }
    }

    //Try to make the first row becomes all zero
    vector<int> toggledColumns = getColumnToggleStatus(M);
    vector<int> toggledRows(N, 0);
    vector<int> rowParitySum(N, 0);

    int countRowWithMixedParity = 0;
    int rowWithMixedParity = -1;
    for (int i = 2; i <= N; i++) {
        int paritySum = 0;
        for (int j = 1; j <= M; j++)
            paritySum += (a[i][j] + toggledColumns[j - 1])%2;

        if (paritySum != 0 && paritySum != M) {
            rowWithMixedParity = i;
            countRowWithMixedParity += 1;
        }

        rowParitySum[i - 1] = paritySum;
    }

    //Toggle some rows to make it sorted
    if (rowWithMixedParity != -1) {
        for (int i = 1; i <= N; i++) {
            if (i < rowWithMixedParity && rowParitySum[i - 1] > 0) toggledRows[i - 1] = 1;
            if (i > rowWithMixedParity && rowParitySum[i - 1] == 0) toggledRows[i - 1] = 1;
            if (i == rowWithMixedParity && (a[i][1] + toggledColumns[0])%2 == 1) toggledRows[i - 1] = 1;
        }
    } else {
        for (int i = 1; i <= N; i++) {
            if (rowParitySum[i - 1] > 0) toggledRows[i - 1] = 1;
        }
    }

    //check if sorted
    for (int i = 1; i <= N; i++) {
        for (int j = 2; j <= N; j++) {
            int curr = (a[i][j] + toggledRows[i - 1] + toggledColumns[j - 1])%2;
            int prv = (a[i][j - 1] + toggledRows[i - 1] + toggledColumns[j - 2])%2;

            if (curr < prv) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    if (countRowWithMixedParity > 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (auto t: toggledRows) cout << t;
        cout << endl;
        for (auto t: toggledColumns) cout << t;
        cout << endl;
    }
}
