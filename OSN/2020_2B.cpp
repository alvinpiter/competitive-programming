#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int
#define INF 1e18

struct Pillar {
  int index, x, y, r;
  Pillar(int _index, int _x, int _y, int _r) {
    index = _index; x = _x, y = _y, r = _r;
  }
};

bool pillarsMinXComparator(Pillar p1, Pillar p2) {
  if (p1.x - p1.r < p2.x - p2.r) {
    return true;
  } else {
    return false;
  }
}

bool pillarsMinYComparator(Pillar p1, Pillar p2) {
  if (p1.y - p1.r < p2.y - p2.r) {
    return true;
  } else {
    return false;
  }
}

int N, Xs, Ys, Xf, Yf, C[MAXN + 3];
LL dist[MAXN + 3][2];
vector<int> horizontalNeighbors[MAXN + 3], verticalNeighbors[MAXN + 3];
vector<Pillar> pillars;

/*
Build vertical network
i.e if a pillar is shone vertically, which pillars will be shone too?
*/
void buildVerticalNetwork() {
  sort(pillars.begin(), pillars.end(), pillarsMinXComparator);

  int maxRight = pillars[0].x + pillars[0].r;
  int lastPillarIndex = pillars[0].index;

  for (int i = 1; i < pillars.size(); i++) {
    if (maxRight >= pillars[i].x - pillars[i].r) {
      verticalNeighbors[lastPillarIndex].push_back(pillars[i].index);
      verticalNeighbors[pillars[i].index].push_back(lastPillarIndex);
    }

    if (pillars[i].x + pillars[i].r > maxRight) {
      maxRight = pillars[i].x + pillars[i].r;
      lastPillarIndex = pillars[i].index;
    }
  }
}

/*
Build horizontal network
i.e if a pillar is shone vertically, which pillars will be shone too?
*/
void buildHorizontalNetwork() {
  sort(pillars.begin(), pillars.end(), pillarsMinYComparator);

  int maxTop = pillars[0].y + pillars[0].r;
  int lastPillarIndex = pillars[0].index;

  for (int i = 1; i < pillars.size(); i++) {
    if (maxTop >= pillars[i].y - pillars[i].r) {
      horizontalNeighbors[lastPillarIndex].push_back(pillars[i].index);
      horizontalNeighbors[pillars[i].index].push_back(lastPillarIndex);
    }

    if (pillars[i].y + pillars[i].r > maxTop) {
      maxTop = pillars[i].y + pillars[i].r;
      lastPillarIndex = pillars[i].index;
    }
  }
}

int main() {
  scanf("%d%d%d%d%d", &N, &Xs, &Ys, &Xf, &Yf);
  for (int i = 1; i <= N; i++) {
    int x, y, r, c;
    scanf("%d%d%d%d", &x, &y, &r, &c);

    pillars.push_back(Pillar(i, x, y, r));
    C[i] = c;
  }

  /*
  Treat (Xf, Yf) as a pillar with r = 0.
  */
  pillars.push_back(Pillar(N + 1, Xf, Yf, 0)); C[N + 1] = 0;

  buildVerticalNetwork();
  buildHorizontalNetwork();

  /*
  Create a new pillar, numbered 0.
  Connect all pillar that is reachable from (Xs, Ys) to this pillar.
  */
  C[0] = 0;
  for (int i = 0; i < pillars.size(); i++) {
    if (Ys >= pillars[i].y - pillars[i].r && Ys <= pillars[i].y + pillars[i].r) {
      horizontalNeighbors[0].push_back(pillars[i].index);
      horizontalNeighbors[pillars[i].index].push_back(0);
    }
  }

  //Execute Dijkstra's algorithm from pillar 0
  for (int i = 0; i <= N + 1; i++) {
    dist[i][0] = dist[i][1] = INF;
  }

  priority_queue<pair<LL, pair<int, int> > > pq;
  dist[0][0] = 0;
  pq.push(make_pair(0, make_pair(0, 0)));

  while (!pq.empty()) {
    pair<LL, pair<int, int> > top = pq.top(); pq.pop();

    LL cost = -top.first;
    int u = top.second.first;
    int direction = top.second.second;

    for (int i = 0; i < horizontalNeighbors[u].size(); i++) {
      int v = horizontalNeighbors[u][i];
      int w = direction == 0 ? 0 : C[u];
      if (dist[v][0] > dist[u][direction] + w) {
        dist[v][0] = dist[u][direction] + w;
        pq.push(make_pair(-dist[v][0], make_pair(v, 0)));
      }
    }

    for (int i = 0; i < verticalNeighbors[u].size(); i++) {
      int v = verticalNeighbors[u][i];
      int w = direction == 0 ? C[u] : 0;
      if (dist[v][1] > dist[u][direction] + w) {
        dist[v][1] = dist[u][direction] + w;
        pq.push(make_pair(-dist[v][1], make_pair(v, 1)));
      }
    }
  }

  LL ans = min(dist[N + 1][0], dist[N + 1][1]);

  if (ans < INF) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
}
