#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, x[MAXN + 3], answer[MAXN + 3];
stack<int> st;

int main() {
    scanf("%d", &n);

    x[0] = 0;
    st.push(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);

        while (x[st.top()] >= x[i])
            st.pop();

        answer[i] = st.top();
        st.push(i);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1)
            cout << " ";

        cout << answer[i];
    }
    cout << endl;
}
