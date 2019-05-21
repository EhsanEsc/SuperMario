#include "ExactRectangle.h"
#include <iostream>

using namespace std;

bool ExactRectangle::intersects(ExactRectangle r) {
    return (x < r.x + w &&
            x + w > r.x &&
            y < r.y + r.h &&
            y + h > r.y);
}

ExactRectangle::ExactRectangle(double _x, double _y, int _w, int _h) :
    x(_x), y(_y), w(_w), h(_h) {}

ExactRectangle ExactRectangle::relative_to_x(int x) {
    ExactRectangle result = *this;
    result.x -= x;
    return result;
}

std::ostream &operator<<(std::ostream &stream, const ExactRectangle r) {
     return stream << "(x: " << r.x << ", y: " << r.y << ", w: " << r.w << ", h: " << r.h
     << ")";
}

