#include "utils/coordinate.hpp"

Coordinate::Coordinate() {
    x = 0;
    y = 0;
}

Coordinate::Coordinate(float x1, float y1) {
    x = x1;
    y = y1;
};

float Coordinate::getX() {
    return x;
}

float Coordinate::getY() {
    return y;
}

void Coordinate::move(Coordinate v) {
    x += v.x;
    y += v.y;
}

std::ostream& operator<<(std::ostream &strm, const Coordinate &c) {
  return strm << "Coordinate(x:" << c.x << " y:" << c.y << ")";
}

bool Coordinate::operator!=(const Coordinate &c2) const {
    return x == c2.x && y == c2.y;
}