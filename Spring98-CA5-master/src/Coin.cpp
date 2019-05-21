#include "Coin.h"
#include "Game.h"

void Coin::update() {
    position.y -= 14;
    if (position.y < original_y - 3 * CELL_SIZE_PX)
        game->remove_object(this);
}

std::string Coin::get_image_addr() const {
    return COIN_ADDR;
}

Coin::Coin(ExactRectangle position, Game *game) :
    MovingObject(position, game) {
    original_y = position.y;
}
