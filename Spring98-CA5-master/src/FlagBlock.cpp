#include "FlagBlock.h"
#include "Mario.h"
#include "Game.h"

FlagBlock::FlagBlock(ExactRectangle position, Game *game, std::string image_addr) :
    Object(position, game) {
    this->image_addr = image_addr;
}

std::string FlagBlock::get_image_addr() const {
    return image_addr;
}

void FlagBlock::update() {}

void FlagBlock::handle_interaction_with_mario(Mario *mario) {
    if (mario->collides(this))
        game->on_win();
}
