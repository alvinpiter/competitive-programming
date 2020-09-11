#include<bits/stdc++.h>
using namespace std;
#define INF 1000000007
#define MAXN 200000

struct City {
    int position, population, index;
    City() {}
    City(int _position, int _population, int _index): position(_position), population(_population), index(_index) {}
};

bool cmpPosition(City a, City b) {
    return a.position < b.position;
}

int main() {
    int n, lef[MAXN + 3], rig[MAXN + 3];
    City cities[MAXN + 3];

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, p;
        scanf("%d%d", &x, &p);

        cities[i] = City(x, p, i);
    }

    sort(cities + 1, cities + n + 1, cmpPosition);
    cities[0] = City(0, INF, 0);
    cities[n + 1] = City(INF, INF, n + 1);

    stack<int> stLeft;
    stLeft.push(0);
    for (int i = 1; i <= n; i++) {
        while (cities[i].population > cities[stLeft.top()].population)
            stLeft.pop();

        lef[i] = stLeft.top();
        stLeft.push(i);
    }

    stack<int> stRight;
    stRight.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (cities[i].population > cities[stRight.top()].population)
            stRight.pop();

        rig[i] = stRight.top();
        stRight.push(i);
    }

    int answer[MAXN + 3];
    for (int i = 1; i <= n; i++) {
        int idx = cities[i].index;

        if (lef[i] == 0 && rig[i] == n + 1)
            answer[idx] = -1;
        else if (lef[i] == 0)
            answer[idx] = cities[rig[i]].index;
        else if (rig[i] == n + 1)
            answer[idx] = cities[lef[i]].index;
        else {
            int distLeft = cities[i].position - cities[lef[i]].position;
            int distRight = cities[rig[i]].position - cities[i].position;

            if (distLeft > distRight)
                answer[idx] = cities[rig[i]].index;
            else if (distLeft < distRight)
                answer[idx] = cities[lef[i]].index;
            else {
                if (cities[lef[i]].population > cities[rig[i]].population)
                    answer[idx] = cities[lef[i]].index;
                else
                    answer[idx] = cities[rig[i]].index;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    printf("\n");
}
