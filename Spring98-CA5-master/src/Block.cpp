#include "Block.h"
#include "AssetsAddresses.h"

using namespace std;

Block::Block(ExactRectangle position, string image_addr, Game* game) :
    Object(position, game) {
    this->image_addr = image_addr;
}

std::string Block::get_image_addr() const {
    return image_addr;
}

void Block::update() {}
