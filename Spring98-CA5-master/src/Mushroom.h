#ifndef SRC_MUSHROOM_H
#define SRC_MUSHROOM_H

#include "AutomaticMovingObject.h"

class Mushroom : public AutomaticMovingObject {
public:
    Mushroom(ExactRectangle position, Game* game);
    void handle_interaction_with_mario(Mario *mario) override;
    void update() override;

private:
    int start_of_movement_delay;
};

class RedMushroom : public Mushroom {
public:
    using Mushroom::Mushroom;
    std::string get_image_addr() const override;

    void handle_interaction_with_mario(Mario *mario) override;
};

class HealthMushroom : public Mushroom {
    using Mushroom::Mushroom;
public:
    void handle_interaction_with_mario(Mario *mario) override;
    std::string get_image_addr() const override;
};

#endif //SRC_MUSHROOM_H
