#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n;
double x[MAXN + 3], maxr[MAXN + 3], r[MAXN + 3];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> maxr[i];

    r[1] = maxr[1];

    stack<pair<double, double> > st;
    st.push({x[1], r[1]});

    for (int i = 2; i <= n; i++) {
        r[i] = maxr[i];

        while (!st.empty()) {
            auto top = st.top();
            double prevX = top.first;
            double prevR = top.second;

            r[i] = min(r[i], (x[i] - prevX)*(x[i] - prevX)/(4 * prevR));

            if (r[i] >= prevR)
                st.pop();
            else
                break;
        }

        st.push({x[i], r[i]});
    }

    for (int i = 1; i <= n; i++)
        printf("%.5lf\n", r[i]);
}
