#include<bits/stdc++.h>
using namespace std;
#define MAXK 1000

int K, N, cnt[MAXK + 3];

bool checkValidity() {
    int n = 0;

    for (int i = 1; i <= K; i++)
        n += cnt[i];

    for (int i = 1; i <= K; i++) {
        if (cnt[i] != n/K)
            return false;
    }

    return true;
}

int main() {
    cin >> K >> N;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; i++) {
        int s;
        cin >> s;

        cnt[s] += 1;
    }

    //try +x
    for (int i = 1; i <= K; i++) {
        cnt[i] += 1;

        if (checkValidity()) {
            cout << "+" << i << endl;
            return 0;
        } else {
            cnt[i] -= 1;
        }
    }

    //try -x
    for (int i = 1; i <= K; i++) {
        cnt[i] -= 1;

        if (checkValidity()) {
            cout << "-" << i << endl;
            return 0;
        } else {
            cnt[i] += 1;
        }
    }

    //try -x +y
    int idxMore = -1, idxLess = -1, cntCorrect = 0;
    for (int i = 1; i <= K; i++) {
        if (cnt[i] == N/K)
            cntCorrect += 1;
        else if (cnt[i] == N/K - 1)
            idxLess = i;
        else if (cnt[i] == N/K + 1)
            idxMore = i;
    }

    if (N%K != 0 || idxMore == -1 || idxLess == -1 || cntCorrect != K - 2)
        cout << "*\n";
    else
        cout << "-" << idxMore << " +" << idxLess << endl;
}
