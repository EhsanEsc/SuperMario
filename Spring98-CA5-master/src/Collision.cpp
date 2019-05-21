#include "Collision.h"

using namespace std;

Collision::Collision(bool from_top, bool from_bottom, bool from_left, bool from_right) {
    this->from_top = from_top;
    this->from_bottom = from_bottom;
    this->from_left = from_left;
    this->from_right = from_right;
}

Collision::Collision() {
    this->from_top = this->from_bottom = this->from_right = this->from_left = false;
}

Collision Collision::NO_COLLISION(false, false, false, false);

bool Collision::operator==(const Collision &c) {
    return from_top == c.from_top &&
           from_bottom == c.from_bottom &&
           from_right == c.from_right &&
           from_left == c.from_left;
}

bool Collision::operator!=(const Collision &c) {
    return !(*this == c);
}

Collision Collision::aggregate(Collision col) const {
    if (this->collides_from_n_sides() == 1 && col.collides_from_n_sides() == 2)
        return *this;
    else if (this->collides_from_n_sides() == 2 && col.collides_from_n_sides() == 1)
        return col;
    else {
        Collision result = *this;
        result.from_top = result.from_top || col.from_top;
        result.from_bottom = result.from_bottom || col.from_bottom;
        result.from_left = result.from_left || col.from_left;
        result.from_right = result.from_right || col.from_right;
        return result;
    }
}

int Collision::collides_from_n_sides() const{
    int result = 0;
    if (from_top) result++;
    if (from_bottom) result++;
    if (from_left) result++;
    if (from_right) result++;
    return result;
}

ostream& operator<<(ostream &stream, const Collision col) {
    return stream<<"{t:"<<col.from_top<<", b:"<<col.from_bottom<<", l:"<<col.from_left<<", r:"<<col.from_right<<"}"<<endl;
}

