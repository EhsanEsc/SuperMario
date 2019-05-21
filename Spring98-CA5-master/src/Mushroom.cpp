#include "Mushroom.h"
#include "AssetsAddresses.h"
#include "Game.h"

Mushroom::Mushroom(ExactRectangle position, Game *game) :
    AutomaticMovingObject(position, game) {
    vx = +10;
    start_of_movement_delay = 10;
}

void Mushroom::update() {
    start_of_movement_delay--;
    if (start_of_movement_delay > 0)
        return;
    AutomaticMovingObject::update();
}

void Mushroom::handle_interaction_with_mario(Mario *mario) {
    if (mario->collides(this))
        game->remove_object(this);
}

std::string RedMushroom::get_image_addr() const {
    return RED_MUSHROOM_ADDR;
}

void RedMushroom::handle_interaction_with_mario(Mario *mario) {
    if (mario->collides(this))
        game->play_sound_effect(RED_MUSHROOM_SOUND);

    Mushroom::handle_interaction_with_mario(mario);
}


void HealthMushroom::handle_interaction_with_mario(Mario *mario) {
    if (mario->collides(this)) {
        game->increment_lives();
        game->play_sound_effect(HEALTH_MUSHROOM_SOUND);
    }

    Mushroom::handle_interaction_with_mario(mario);
}

std::string HealthMushroom::get_image_addr() const {
    return HEALTH_MUSHROOM_ADDR;
}

