#ifndef SRC_AUTOMATICMOVINGOBJECT_H
#define SRC_AUTOMATICMOVINGOBJECT_H

#include "Object.h"

class AutomaticMovingObject : public MovingObject {
public:
    using MovingObject::MovingObject;
    void update() override;
};

#endif //SRC_AUTOMATICMOVINGOBJECT_H
