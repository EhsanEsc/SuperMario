#ifndef SRC_MAPREADER_H
#define SRC_MAPREADER_H

#include <string>
#include <vector>

class Game;
typedef std::vector<std::vector<char>> charmap;

class MapReader {
public:
    static MapReader* get_instance();
    void read(std::string file_name, Game* game);
private:
    MapReader();
    void load_map_cell(int x, int y, char cell, char annotation, Game* game);
    charmap annotate_map(const charmap& map);
    char annotate_cell(int i, int j, const charmap& map);

    static MapReader* instance;
};

#endif //SRC_MAPREADER_H
