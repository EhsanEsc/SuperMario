#ifndef SRC_FLAG_H
#define SRC_FLAG_H

#include "Object.h"

class FlagBlock : public Object {
public:
    FlagBlock(ExactRectangle position, Game* game, std::string image_addr);
    void update() override;
    std::string get_image_addr() const override;
    void handle_interaction_with_mario(Mario *mario) override;

private:
    std::string image_addr;
};

#endif
