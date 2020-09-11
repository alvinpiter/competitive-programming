#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

struct Event {
    int when, value, type;
    Event() {}
    Event(int _when, int _value, int _type): when(_when), value(_value), type(_type) {}
};

bool compareEvent(Event a, Event b) {
    return a.when < b.when;
}

int N, Q;
vector<Event> events;

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; i++) {
        int S, T, X;
        scanf("%d%d%d", &S, &T, &X);

        events.push_back({S - X, X, +1});
        events.push_back({T - X, X, -1});
    }

    sort(events.begin(), events.end(), compareEvent);

    int ptrEvent = 0;
    multiset<int> Xs;
    for (int i = 0; i < Q; i++) {
        int D;
        scanf("%d", &D);

        while (ptrEvent < events.size() && D >= events[ptrEvent].when) {
            auto event = events[ptrEvent];
            if (event.type == 1)
                Xs.insert(event.value);
            else
                Xs.erase(Xs.find(event.value));

            ptrEvent += 1;
        }

        if (Xs.size() == 0)
            printf("-1\n");
        else
            printf("%d\n", *(Xs.begin()));
    }
}
