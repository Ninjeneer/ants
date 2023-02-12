#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class Coordinate {
private:
    int x;
    int y;

public:
    Coordinate();

    Coordinate(float x, float y);

    float getX();

    float getY();

    void move(Coordinate v);

    friend std::ostream &operator<<(std::ostream &, const Coordinate &);

    bool operator!=(const Coordinate &c2) const;
};

#endif