#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int N, A[MAXN + 3], startA, startB, answerA, answerB;
string dirA, dirB;

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    cin >> startA >> dirA;
    cin >> startB >> dirB;

    answerA = 0;
    for (int i = startA; i >= 1 && i <= N; i += (dirA == "right" ? 1 : -1))
        answerA += A[i];

    answerB = 0;
    for (int i = startB; i >= 1 && i <= N; i += (dirB == "right" ? 1 : -1))
        answerB += (A[i] == 0 ? 1 : 0);

    cout << answerA << " " << answerB << endl;
}
