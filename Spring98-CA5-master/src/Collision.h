#ifndef SRC_COLLISION_H
#define SRC_COLLISION_H

#include <iostream>

struct Collision {
    bool from_top, from_bottom, from_left, from_right;
    Collision(bool from_top, bool from_bottom, bool from_left, bool from_right);
    Collision();
    Collision aggregate(Collision col) const;
    bool operator==(const Collision& c);
    bool operator!=(const Collision& c);
    int collides_from_n_sides() const;

    static Collision NO_COLLISION;
};
std::ostream& operator<<(std::ostream &stream, const Collision);



#endif //SRC_COLLISION_H
