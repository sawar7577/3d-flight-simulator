#include "main.h"



std::vector <Point> returnRectangles(Point a, Point b, Point c, Point d) {
    std::vector <Point> rec;
    rec.push_back(a);
    rec.push_back(b);
    rec.push_back(c);
    rec.push_back(c);
    rec.push_back(d);
    rec.push_back(a);
    return rec;
}
