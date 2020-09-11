#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

struct Segment {
    int l, r, index;
    Segment(int _l, int _r, int _index): l(_l), r(_r), index(_index) {}
};

bool cmpSegment(Segment a, Segment b) {
    return a.l < b.l;
}

int main() {
    int n, m;
    vector<Segment> segments;

    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        segments.push_back(Segment(l, r, i));
    }

    sort(segments.begin(), segments.end(), cmpSegment);

    int ptrSegment = 0;
    int currentPosition = 1;

    priority_queue<pair<int, int> > pq; //{right end, index}
    vector<int> answer;
    while (currentPosition != m + 1) {
        //enqueue all potential segments
        while (ptrSegment < n && segments[ptrSegment].l <= currentPosition) {
            pq.push({segments[ptrSegment].r, segments[ptrSegment].index});
            ptrSegment += 1;
        }

        //remove all invalid segments
        while (!pq.empty() && pq.top().first < currentPosition)
            pq.pop();

        if (pq.empty()) {
            break;
        } else {
            auto top = pq.top();
            currentPosition = top.first + 1;
            answer.push_back(top.second);
        }
    }

    if (currentPosition != m + 1)
        printf("NO\n");
    else {
        printf("YES\n");
        printf("%d\n", (int) answer.size());
        for (auto a: answer)
            printf("%d ", a + 1);
        printf("\n");
    }
}
