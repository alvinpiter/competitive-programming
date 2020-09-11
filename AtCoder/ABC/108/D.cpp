#include<bits/stdc++.h>
using namespace std;

int main() {
    int L, N;
    vector<pair<pair<int, int>, int> > edges;

    cin >> L;

    //Find most significant bit of L
    for (int lg = 20; lg >= 0; lg--) {
        if (L & (1 << lg)) {
            N = lg;
            break;
        }
    }

    //Create graph with N + 1 vertices and 2 * N edges. Node i is connected with node i + 1 with 2 edges, each with weight 0 and 2^(i - 1)
    for (int i = 1; i <= N; i++) {
        edges.push_back({{i, i + 1}, 0});
        edges.push_back({{i, i + 1}, (1 << (i - 1))});
    }

    //For other on bits in i in L, we add an edge from vertex i + 1 to vertex N + 1 and it's weight is equal to sum of previous on bits
    int sum = (1 << N);
    for (int lg = N - 1; lg >= 0; lg--) {
        if (L & (1 << lg)) {
            edges.push_back({{lg + 1, N + 1}, sum});
            sum += (1 << lg);
        }
    }

    cout << N + 1 << " " << (int) edges.size() << endl;
    for (auto edge: edges)
        cout << edge.first.first << " " << edge.first.second << " " << edge.second << endl;
}
