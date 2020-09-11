#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

/*
Line sweep + a little bit of geometry.
Learned strict weak ordering.
*/

struct Line {
    int x1, y1, x2, y2;
    Line() {}
    Line(int _x1, int _y1, int _x2, int _y2): x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    bool operator<(Line other) const {
        if (other.x2 > x2) {
            //Make sure (x2, y2) is below other line
            return ((LL) y2 - other.y1) * (other.x2 - other.x1) < ((LL) other.y2 - other.y1) * (x2 - other.x1);
        } else {
            //Make sure (other.x2, other.y2) is above current line
            return ((LL) other.y2 - y1) * (x2 - x1) > ((LL) y2 - y1) * (other.x2 - x1);
        }
    }
};

struct Event {
    int x, type;
    Line line;
    Event(int _x, Line _line, int _type): x(_x), line(_line), type(_type) {}
    bool operator<(Event other) const {
        return x < other.x;
    }
};

int N;
Line currentLine;
vector<Event> events;

int main() {
    freopen("hillwalk.in", "r", stdin);
    freopen("hillwalk.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        Line line = Line(x1, y1, x2, y2);

        if (i == 1)
            currentLine = line;

        events.push_back(Event(x1, line, +1));
        events.push_back(Event(x2, line, -1));
    }

    sort(events.begin(), events.end());

    int answer = 1;
    int ptr = 0;

    multiset<Line> active;
    while (true) {
        //process all events that happens before or at current line right end
        while (ptr < events.size() && events[ptr].x <= currentLine.x2) {
            if (events[ptr].type == 1) {
                active.insert(events[ptr].line);
            } else {
                active.erase(active.find(events[ptr].line));
            }

            ptr += 1;
        }

        if (active.empty())
            break;

        //find which line will be below current line
        auto ptr = active.lower_bound(currentLine);
        if (ptr != active.begin()) {
            Line below = *(--ptr);

            answer += 1;
            currentLine = below;
        } else {
            //no line below current line
            break;
        }
    }

    cout << answer << endl;
}
