#ifndef SRC_PIPEBLOCK_H
#define SRC_PIPEBLOCK_H

#include "Block.h"

class PipeBlock : public Block {
public:
    PipeBlock(ExactRectangle position, char type, Game* game);
};

#endif
