#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

// Cross product of two vectors: (p1 - p0) × (p2 - p0) => O(1)
double cross(const Point& p0, const Point& p1, const Point& p2) {
    return (p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x);
}

// Orientation of triplet (p, q, r) => O(1)
// Returns: 0 -> colinear, 1 -> clockwise, 2 -> counter-clockwise
int orientation(const Point& p, const Point& q, const Point& r) {
    double val = cross(p, q, r);
    if (abs(val) < 1e-9) return 0;
    return (val > 0 ? 2 : 1); // 2 = CCW, 1 = CW
}

// Check if point q lies on segment pr => O(1)
bool onSegment(const Point& p, const Point& q, const Point& r) {
    return min(p.x, r.x) <= q.x && q.x <= max(p.x, r.x) &&
           min(p.y, r.y) <= q.y && q.y <= max(p.y, r.y);
}

// Check if two segments p1q1 and p2q2 intersect => O(1)
bool segmentsIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;

    // Special cases
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// Check for any intersection among a set of segments => O(n^2)
bool hasAnyIntersection(const vector<pair<Point, Point>>& segments) {
    int n = segments.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (segmentsIntersect(segments[i].first, segments[i].second,
                                  segments[j].first, segments[j].second))
                return true;
    return false;
}

// Area of triangle formed by p1, p2, p3 => O(1)
double triangleArea(const Point& p1, const Point& p2, const Point& p3) {
    return abs(cross(p1, p2, p3)) / 2.0;
}

// Check if point p is inside triangle ABC => O(1)
bool pointInTriangle(const Point& p, const Point& a, const Point& b, const Point& c) {
    double A = triangleArea(a, b, c);
    double A1 = triangleArea(p, b, c);
    double A2 = triangleArea(a, p, c);
    double A3 = triangleArea(a, b, p);
    return abs(A - (A1 + A2 + A3)) < 1e-9;
}

// Ray casting algorithm to check if point is inside a polygon => O(n)
bool pointInPolygon(const Point& p, const vector<Point>& polygon) {
    int cnt = 0, n = polygon.size();
    for (int i = 0; i < n; ++i) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        if (a.y > b.y) swap(a, b);
        if (p.y > a.y && p.y <= b.y && (b.y - a.y) > 1e-9) {
            double xInt = a.x + (p.y - a.y) * (b.x - a.x) / (b.y - a.y);
            if (xInt > p.x) ++cnt;
        }
    }
    return cnt % 2 == 1;
}

int main() {
    Point a = {0, 0};
    Point b = {4, 0};
    Point c = {0, 3};

    double area = triangleArea(a, b, c);
    cout << "Area of triangle: " << area << endl;

    return 0;
}