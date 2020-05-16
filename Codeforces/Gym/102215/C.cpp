#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
We would like to know how many possible remainder when i*(i + 1)/2 is divided by p.
Notice when we substitute i with 2*p, i*(i + 1)/2 is divisible by p and after that the result will cycle.
*/

LL p, n;
int current;
bool visited[10000003];

int main() {
    cin >> p >> n;

    memset(visited, false, sizeof(visited));
    visited[0] = true;

    current = 0;
    for (int i = 1; i <= min(2 * p, n); i++) {
        current = (current + i)%p;
        visited[current] = true;
    }

    int answer = 0;
    for (int i = 0; i < p; i++) {
        answer += (visited[i] ? 1 : 0);
    }

    cout << answer << endl;
}
