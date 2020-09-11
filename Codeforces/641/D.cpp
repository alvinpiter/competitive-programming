#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Observation 1:
If there are 2 consecutive k in the array, then the answer is yes. We can always take 3 consective numbers, 2 k and 1 other number and the median will be k. Do it repeatedly

Algorithm:
* If there is no k in the array, then no.
* If there is 2 consecutive numbers which is >= k, then yes. Proof:
    * If both numbers are k, then we can use first observation.
    * If one of the number is k, then we can convert these two numbers into 2 k. Then back to first observation.
    * If both numbers are > k, we can "spread" it until it "touches" 1 k. Then back to previous point.
* If there are 2 numbers which is >= k and their position differs by two, then yes. We can take these two numbers and 1 smaller number in the middle. The median will be >= k. Then back to previous point.
* If none of the above is fulfilled, then no. Proof:
    Every number number which is >= k will be separated by at least 2 numbers which is < k. Whatever subarray we take, the number of numbers which is < k will be at least half the length of array (for example: large small small large), hence the median will be < k.
*/

int main() {
    int t, n, k, a[MAXN + 3];

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &k);

        bool kExist = false;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if (a[i] == k)
                kExist = true;
        }

        if (!kExist) {
            printf("no\n");
            continue;
        }

        //special case
        if (n == 1) {
            printf("yes\n");
            continue;
        }

        int lastLargerOrEqual = -1;
        bool possible = false;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= k) {
                if (lastLargerOrEqual != -1 && i - lastLargerOrEqual <= 2)
                    possible = true;

                lastLargerOrEqual = i;
            }
        }

        if (possible)
            printf("yes\n");
        else
            printf("no\n");
    }
}
