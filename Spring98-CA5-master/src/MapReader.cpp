#include "MapReader.h"
#include "PipeBlock.h"
#include "Block.h"
#include <fstream>
#include "Game.h"

using namespace std;

MapReader* MapReader::instance = nullptr;

MapReader::MapReader() {} //just to make sure no other class instantiates MapReader

MapReader* MapReader::get_instance() {
    if (instance == nullptr)
        instance = new MapReader;
    return instance;
}

void MapReader::read(std::string file_name, Game *game) {

    ifstream level_file(file_name.c_str());

    string line;
    charmap map;
    while(getline(level_file, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++)
            row.push_back(line[i]);
        map.push_back(row);
    }

    charmap annotations = annotate_map(map);

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            load_map_cell(j, i, map[i][j], annotations[i][j], game);
        }
    }
}

void MapReader::load_map_cell(int x, int y, char cell, char annotation, Game* game) {
    ExactRectangle position(x * CELL_SIZE_PX, y * CELL_SIZE_PX, CELL_SIZE_PX, CELL_SIZE_PX);
    switch(cell) {
        case '#':
            game->add_block(new Block(position, GROUND_BLOCK_ADDR, game)); break;
        case '@':
            game->add_block(new Block(position, REGULAR_BLOCK_ADDR, game)); break;
        case 'M':
            game->set_mario(new Mario(position, game)); break;
        case 'b':
            game->add_brick(new RegularBrick(position, game)); break;
        case '?':
            game->add_brick(new QuestionBrick(position, game, COIN)); break;
        case 'm':
            game->add_brick(new QuestionBrick(position, game, RED_MUSHROOM)); break;
        case 'h':
            game->add_brick(new QuestionBrick(position, game, HEALTH_MUSHROOM)); break;
        case 'l':
            game->add_enemy(new LittleGoomba(position, game)); break;
        case 'k':
            game->add_enemy(new KoopaTroopa(position, game)); break;
        case '|':
            game->add_block(new PipeBlock(position, annotation, game)); break;
        case 'f': {
            game->add_object(new FlagBlock(position,
                    game, string(FLAG_ADDR) + (annotation == 'h' ? "head" : "body") + ".png"));
            break;
        }
        case '.':
            break;
        default:
            cout<<"invalid chracter "<<cell<<" in map. exiting."<<endl;
            exit(EXIT_FAILURE);
    }
}


charmap MapReader::annotate_map(const charmap& map) {
    charmap result;
    for (int i = 0; i < map.size(); i++) {
        vector<char> row;
        for (int j = 0; j < map[i].size(); j++) {
            row.push_back(annotate_cell(i, j, map));
        }
        result.push_back(row);
    }
    return result;
}

char MapReader::annotate_cell(int i, int j, const charmap &map) {
    if (map[i][j] == '|') {
        if (map[i - 1][j] != '|' && map[i][j - 1] != '|')
            return 'L';
        else if (map[i - 1][j] != '|' && map[i][j + 1] != '|')
            return 'R';
        else if (map[i][j - 1] != '|')
            return 'l';
        else if (map[i][j + 1] != '|')
            return 'r';
    } else if (map[i][j] == 'f') {
        if (map[i-1][j] != 'f')
            return 'h';
        else
            return 'b';
    } else {
        return ' ';
    }
}
