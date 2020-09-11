#include<bits/stdc++.h>
using namespace std;
#define LL long long int

class F {
private:
    multiset<int> lowA, highA;
    LL sumA, sumLowA, sumHighA, sumB;

public:
    F() {
        sumA = sumLowA = sumHighA = sumB = 0;
    }

    void insert(int a, int b) {
        if (lowA.size() > 0 && a <= *lowA.rbegin()) {
            lowA.insert(a);
            sumLowA += a;

            //balancing
            while (lowA.size() - highA.size() > 1) {
                auto ptr = --(lowA.end());
                int val = *ptr;

                lowA.erase(ptr);
                sumLowA -= val;

                highA.insert(val);
                sumHighA += val;
            }
        } else {
            highA.insert(a);
            sumHighA += a;

            //balancing
            while (highA.size() > lowA.size()) {
                auto ptr = highA.begin();
                int val = *ptr;

                highA.erase(ptr);
                sumHighA -= val;

                lowA.insert(val);
                sumLowA += val;
            }
        }

        sumB += b;
    }

    pair<int, LL> query() {
        int szLow = (int) lowA.size();
        int szHigh = (int) highA.size();

        int x = *lowA.rbegin();

        LL result = ((LL) x * szLow - sumLowA) + (sumHighA - (LL) x * szHigh) + sumB;
        return {x, result};
    }
};

int Q;
F f = F();

int main() {
    scanf("%d", &Q);
    for (int q = 1; q <= Q; q++) {
        int t, a, b;
        scanf("%d", &t);

        if (t == 1) {
            scanf("%d%d", &a, &b);
            f.insert(a, b);
        } else {
            auto answer = f.query();
            printf("%d %lld\n", answer.first, answer.second);
        }
    }
}
