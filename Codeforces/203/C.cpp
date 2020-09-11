#include<bits/stdc++.h>
using namespace std;

int n;
vector<pair<int, pair<int, int> > > bombs;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        bombs.push_back({abs(x) + abs(y), {x, y}});
    }

    sort(bombs.begin(), bombs.end());

    int cnt = 0;
    for (int i = 0; i < bombs.size(); i++) {
        if (bombs[i].second.first == 0 || bombs[i].second.second == 0)
            cnt += 2;
        else
            cnt += 4;

        cnt += 1; //pick it up
        cnt += 1; //destroy it
    }

    printf("%d\n", cnt);
    for (int i = 0; i < bombs.size(); i++) {
        int x = bombs[i].second.first;
        int y = bombs[i].second.second;

        if (x != 0)
            printf("1 %d %c\n", abs(x), (x > 0 ? 'R' : 'L'));

        if (y != 0)
            printf("1 %d %c\n", abs(y), (y > 0 ? 'U' : 'D'));

        printf("2\n");

        if (x != 0)
            printf("1 %d %c\n", abs(x), (x > 0 ? 'L' : 'R'));

        if (y != 0)
            printf("1 %d %c\n", abs(y), (y > 0 ? 'D' : 'U'));

        printf("3\n");
    }
}
