#include "PipeBlock.h"
#include "AssetsAddresses.h"

using namespace std;

PipeBlock::PipeBlock(ExactRectangle position, char type, Game *game) :
    Block(position, "", game) {
    string img_name;
    switch (type) {
        case 'L':
            img_name = "head-left"; break;
        case 'R':
            img_name = "head-right"; break;
        case 'l':
            img_name = "left"; break;
        case 'r':
            img_name = "right"; break;
    }

    this->image_addr = PIPE_ADDR + img_name + ".png";
}
