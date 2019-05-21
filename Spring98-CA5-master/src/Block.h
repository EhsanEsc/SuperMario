#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include <string>

class Block : public Object {
public:
    Block(ExactRectangle position, std::string image_addr, Game* game);
    std::string get_image_addr() const override;
    void update() override;

protected:
    std::string image_addr;
};

#endif
