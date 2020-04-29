#include<bits/stdc++.h>
using namespace std;
#define MAX 2000

/*
First construct a circle graph, i.e the edges are 1-2, 2-3, 3-4,...,(n-1)-n,n-1. This guarantees the degree of each node is 2.
Find a prime number larger than or equal to n, let's say it is nextPrime. We need to add (nextPrime - n) more edges to this graph.
To do this, we can add n/2 edges on our circle graph. One way to do this is by adding edge from i to i + n/2. This guarantees the degree of each node is either 2 or 3.

This algorithm works because for n <= 1000, there must be a prime betwee n and n + n/2.
*/

int main() {
    bool isPrime[MAX + 3];

    for (int i = 1; i <= MAX; i++)
        isPrime[i] = true;

    for (int i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= MAX; j += i)
                isPrime[j] = false;
        }
    }

    int n, nextPrime;

    cin >> n;
    for (int p = 1; p <= MAX; p++) {
        if (isPrime[p] && p >= n) {
            nextPrime = p;
            break;
        }
    }

    cout << nextPrime << endl;
    for (int i = 1; i < n; i++)
        cout << i << " " << i + 1 << endl;

    cout << n << " " << 1 << endl;

    int leftOver = nextPrime - n;
    for (int i = 1; i <= n/2, leftOver > 0; i++, leftOver--) {
        cout << i << " " << i + n/2 << endl;
    }
}
