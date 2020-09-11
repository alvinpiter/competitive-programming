#include<bits/stdc++.h>
using namespace std;
#define Vector pair<int, int>
#define PI 3.14159265358
#define eps 1e-8

//v1 - v2
Vector substract(Vector v1, Vector v2) {
    return make_pair(v1.first - v2.first, v1.second - v2.second);
}

//|v|
double length(Vector v) {
    return sqrt(v.first * v.first + v.second * v.second);
}

//v1.v2
int dotProduct(Vector v1, Vector v2) {
    return v1.first * v2.first + v1.second * v2.second;
}

double angle(Vector v1, Vector v2) {
    double cosValue = dotProduct(v1, v2)/(length(v1) * length(v2));
    return acos(cosValue);
}

int main() {
    int x1, y1, x2, y2;
    int vx1, vy1, vx2, vy2;

    cin >> x1 >> y1 >> x2 >> y2;
    cin >> vx1 >> vy1 >> vx2 >> vy2;

    Vector v = substract(make_pair(vx2, vy2), make_pair(vx1, vy1)); //velocity of second relative to first
    Vector p = substract(make_pair(x2, y2), make_pair(x1, y1)); //position of second relative to first

    if (length(p) <= eps)
        printf("%.10f\n", length(p));
    else if (length(v) <= eps)
        printf("%.10f\n", length(p));
    else {
        double ang = abs(angle(p, v));
        if (PI/2 - ang >= eps) {
            printf("%.10lf\n", length(p));
        } else {
            printf("%.10lf\n", length(p) * cos(ang - PI/2));
        }
    }
}
