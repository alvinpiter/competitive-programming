#include<bits/stdc++.h>
using namespace std;
#define MAXN 100
#define MAXM 2000

int N, M, rate[MAXN + 3], weight[MAXM + 3], carSpace[MAXM + 3], answer;
queue<int> carQueue;
set<int> availableSpace;

void assignCarToParkingSpace(int carIdx) {
    auto ptr = availableSpace.begin();
    int spaceIdx = *ptr;

    answer += weight[carIdx] * rate[spaceIdx];
    carSpace[carIdx] = spaceIdx;
    availableSpace.erase(ptr);
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> rate[i];

    for (int i = 1; i <= M; i++)
        cin >> weight[i];

    for (int i = 1; i <= N; i++)
        availableSpace.insert(i);

    answer = 0;
    for (int i = 1; i <= 2 * M; i++) {
        int car;
        cin >> car;

        if (car > 0) {
            if (availableSpace.empty()) {
                carQueue.push(car);
            } else {
                assignCarToParkingSpace(car);
            }
        } else {
            availableSpace.insert(carSpace[-car]);
            if (!carQueue.empty()) {
                assignCarToParkingSpace(carQueue.front());
                carQueue.pop();
            }
        }
    }

    cout << answer << endl;
}
