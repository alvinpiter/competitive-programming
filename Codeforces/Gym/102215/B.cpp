#include<bits/stdc++.h>
using namespace std;

string top, bottom;
int n, cntTop, cntBottom, cntBoth;
char grid[2][1003];

//type = {0, 1, 2, 3} = {top, bottom, both, none}
void put(int c, int typ) {
    switch (typ) {
        case 0:
            grid[0][c] = '#';
            grid[1][c] = '.';
            break;
        case 1:
            grid[0][c] = '.';
            grid[1][c] = '#';
            break;
        case 2:
            grid[0][c] = '#';
            grid[1][c] = '#';
            break;
        case 3:
            grid[0][c] = '.';
            grid[1][c] = '.';
    }
}

int main() {
    cin >> top >> bottom;

    n = (int) top.length();
    cntTop = cntBottom = cntBoth = 0;

    for (int i = 0; i < n; i++) {
        if (top[i] == '#' && bottom[i] == '#')
            cntBoth += 1;
        else if (top[i] == '#')
            cntTop += 1;
        else if (bottom[i] == '#')
            cntBottom += 1;
    }

    for (int c = 0; c < cntTop; c++)
        put(c, 0);

    for (int c = cntTop; c < cntTop + cntBoth; c++)
        put(c, 2);

    for (int c = cntTop + cntBoth; c < cntTop + cntBoth + cntBottom; c++)
        put(c, 1);

    for (int c = cntTop + cntBoth + cntBottom; c < n; c++)
        put(c, 3);

    if (cntTop > 0 && cntBottom > 0 && cntBoth == 0)
        cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++)
                cout << grid[i][j];

            cout << endl;
        }
    }
}
