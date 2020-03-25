#include<bits/stdc++.h>
using namespace std;
#define MAXA 200000

int main() {
    //dp[i] -> largest index j such that all counter from i to j is at least 2
    int N, counter[MAXA + 3], prefixSumCounter[MAXA + 3], dp[MAXA + 3];

    scanf("%d", &N);

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);

        counter[a] += 1;
    }

    prefixSumCounter[0] = 0;
    for (int i = 1; i <= MAXA; i++)
        prefixSumCounter[i] = prefixSumCounter[i - 1] + counter[i];

    dp[MAXA + 1] = -1;
    for (int i = MAXA; i >= 1; i--) {
        if (counter[i] >= 2) {
            dp[i] = (dp[i + 1] == -1 ? i : dp[i + 1]);
        } else {
            dp[i] = -1;
        }
    }

    int longest = 0, ansL, ansR;
    for (int i = 1; i <= MAXA; i++) {
        //Construct circle with only 1 number
        if (counter[i] > 0) {
            if (counter[i] > longest) {
                longest = counter[i];
                ansL = i;
                ansR = i;
            }
        }

        //Construct circle with 2 numbers
        if (counter[i] > 0 && counter[i + 1] > 0) {
            if (counter[i] + counter[i + 1] > longest) {
                longest = counter[i] + counter[i + 1];
                ansL = i;
                ansR = i + 1;
            }
        }

        //Construct circle with at least 3 numbers
        int j = dp[i + 1];
        if (counter[i] > 0 && j != -1) {
            int ctr = counter[i] + (prefixSumCounter[j] - prefixSumCounter[i]) + counter[j + 1];
            if (ctr > longest) {
                longest = ctr;
                ansL = i;
                ansR = (counter[j + 1] > 0 ? j + 1 : j); //It's possible that counter[j + 1] is 0
            }
        }
    }

    //construct answer
    vector<int> answer;
    for (int i = ansL; i <= ansR; i++) answer.push_back(i);
    for (int i = ansR; i >= ansL; i--) {
        for (int j = 1; j <= counter[i] - 1; j++)
            answer.push_back(i);
    }

    printf("%d\n", (int) answer.size());
    for (int i = 0; i < answer.size(); i++)
        printf("%d ", answer[i]);
    printf("\n");
}
