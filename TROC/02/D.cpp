#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXV 50000

pair<int, vector<int> > generate(int base, int multiplier, int mod) {
    int seenAt[MAXV + 3];
    memset(seenAt, -1, sizeof(seenAt));

    int current = base;
    int cycleStartAt;
    vector<int> numbers;

    numbers.push_back(current);
    seenAt[current] = 0;
    for (int i = 1; ; i++) {
        current = ((LL) current * multiplier)%mod;

        if (seenAt[current] != -1) {
            cycleStartAt = seenAt[current];
            break;
        } else {
            numbers.push_back(current);
            seenAt[current] = i;
        }
    }

    return make_pair(cycleStartAt, numbers);
}

void populateCounter(int counter[], int n, int base, int multiplier, int mod) {
    pair<int, vector<int> > pattern = generate(base, multiplier, mod);
    vector<int> numbers = pattern.second;
    int cycleStartAt = pattern.first;
    int cycleLength = numbers.size() - cycleStartAt;
    int numCycle = (n - cycleStartAt)/cycleLength;
    int rem = n - (numCycle * cycleLength + cycleStartAt);

    //Increase the non-cycle number
    for (int i = 0; i < cycleStartAt; i++)
        counter[numbers[i]] += 1;

    //Increase the cycle number
    for (int i = cycleStartAt; i < numbers.size(); i++)
        counter[numbers[i]] += numCycle;

    //Increase the left over
    for (int i = 0; i < rem; i++)
        counter[numbers[cycleStartAt + i]] += 1;
}

int main() {
    int N, X, Y, C, D, M1, M2;
    int counter1[MAXV + 3], counter2[MAXV + 3];

    memset(counter1, 0, sizeof(counter1));
    memset(counter2, 0, sizeof(counter2));

    cin >> N >> X >> Y >> C >> D >> M1 >> M2;

    populateCounter(counter1, N, X, C, M1);
    populateCounter(counter2, N, Y, D, M2);

    LL answer = 0;
    int ptr1 = MAXV;
    int ptr2 = MAXV;
    int rem = N;
    while (rem > 0) {
        while (counter1[ptr1] == 0)
            ptr1 -= 1;

        while (counter2[ptr2] == 0)
            ptr2 -= 1;

        int take = min(counter1[ptr1], counter2[ptr2]);

        counter1[ptr1] -= take;
        counter2[ptr2] -= take;
        rem -= take;

        answer += ((LL) take * ptr1 * ptr2);
    }

    cout << answer << endl;
}
