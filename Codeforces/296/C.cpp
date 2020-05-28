#include<bits/stdc++.h>
using namespace std;
#define LL long long int

class MaxSegmentLengthDS {
private:
    set<int> pos;
    multiset<int> segmentLengths;

public:
    MaxSegmentLengthDS(int len) {
        pos.insert(0);
        pos.insert(len);

        segmentLengths.insert(len);
    }

    void cut(int p) {
        auto ptr = pos.lower_bound(p);

        int r = *ptr;
        int l = *(--ptr);
        int len = r - l;

        segmentLengths.erase(segmentLengths.find(len));
        segmentLengths.insert(p - l);
        segmentLengths.insert(r - p);

        pos.insert(p);
    }

    int getMaxSegmentLength() {
        return *(--segmentLengths.end());
    }
};

int main() {
    int w, h, n;

    scanf("%d%d%d", &w, &h, &n);

    MaxSegmentLengthDS vCut = MaxSegmentLengthDS(w);
    MaxSegmentLengthDS hCut = MaxSegmentLengthDS(h);

    for (int i = 1; i <= n; i++) {
        char t[2];
        int p;

        scanf("%s%d", t, &p);
        if (t[0] == 'H') {
            hCut.cut(p);
        } else if (t[0] == 'V') {
            vCut.cut(p);
        }

        int maxWidth = vCut.getMaxSegmentLength();
        int maxHeight = hCut.getMaxSegmentLength();

        printf("%lld\n", (LL) maxWidth * maxHeight);
    }
}
