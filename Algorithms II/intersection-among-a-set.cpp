#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Segment {
    Point p, q;
    int id;
    Segment(Point p, Point q, int id) : p(p), q(q), id(id) {
        if (q.x < p.x || (q.x == p.x && q.y < p.y)) std::swap(this->p, this->q);
    }

    // Get y-coordinate of segment at vertical line x
    double getY(double x) const {
        if (fabs(p.x - q.x) < EPS) return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

bool segmentsIntersect(const Segment& a, const Segment& b);

struct Event {
    double x;
    int type; // 0 = left endpoint, 1 = right endpoint
    Segment* segment;
    bool operator<(const Event& e) const {
        if (fabs(x - e.x) > EPS) return x < e.x;
        return type < e.type;
    }
};

struct SegmentComp {
    mutable double x;
    bool operator()(const Segment* a, const Segment* b) const {
        double y1 = a->getY(x);
        double y2 = b->getY(x);
        if (fabs(y1 - y2) > EPS) return y1 < y2;
        return a->id < b->id;
    }
};

bool hasAnyIntersection(vector<Segment>& segments) {
    vector<Event> events;
    for (Segment& seg : segments) {
        events.push_back({seg.p.x, 0, &seg});
        events.push_back({seg.q.x, 1, &seg});
    }
    sort(events.begin(), events.end());

    SegmentComp comp;
    set<Segment*, SegmentComp> active(comp);

    for (const Event& e : events) {
        comp.x = e.x;
        Segment* s = e.segment;

        if (e.type == 0) { // insert
            auto it = active.lower_bound(s);
            auto itNext = it;
            auto itPrev = (it == active.begin() ? active.end() : prev(it));

            if (itNext != active.end() && segmentsIntersect(**itNext, *s)) return true;
            if (itPrev != active.end() && segmentsIntersect(**itPrev, *s)) return true;

            active.insert(it, s);
        } else { // remove
            auto it = active.find(s);
            if (it == active.end()) continue;

            auto itNext = next(it);
            auto itPrev = (it == active.begin() ? active.end() : prev(it));

            if (itNext != active.end() && itPrev != active.end() &&
                segmentsIntersect(**itPrev, **itNext)) return true;

            active.erase(it);
        }
    }
    return false;
}

// Segment intersection using orientation
int orientation(const Point& a, const Point& b, const Point& c) {
    double val = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
    if (fabs(val) < EPS) return 0;
    return (val > 0 ? 1 : 2);
}

bool onSegment(const Point& p, const Point& q, const Point& r) {
    return min(p.x, r.x) <= q.x + EPS && q.x <= max(p.x, r.x) + EPS &&
           min(p.y, r.y) <= q.y + EPS && q.y <= max(p.y, r.y) + EPS;
}

bool segmentsIntersect(const Segment& s1, const Segment& s2) {
    Point p1 = s1.p, q1 = s1.q, p2 = s2.p, q2 = s2.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}


int main() {
    vector<Segment> segs = {
        {{0, 0}, {4, 4}, 0},
        {{0, 4}, {4, 0}, 1},
        {{5, 5}, {6, 6}, 2}
    };
    cout << (hasAnyIntersection(segs) ? "YES" : "NO") << endl;
    return 0;
}
