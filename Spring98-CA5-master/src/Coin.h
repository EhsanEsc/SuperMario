#ifndef SRC_COIN_H
#define SRC_COIN_H

#include "Object.h"

class Coin : public MovingObject {
public:
    Coin(ExactRectangle position, Game* game);
    void update() override;
    std::string get_image_addr() const override;
private:
    double original_y;
};

#endif
