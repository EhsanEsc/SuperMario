#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddresses.h"
#include "Mario.h"
#include "Block.h"
#include "Brick.h"
#include "Enemy.h"
#include "FlagBlock.h"
#include <string>
#include <vector>

#define CELL_SIZE_PX 32

class Mario;

class Game {
public:
    Game();
    void run_level(std::string level_addr);
    ~Game();

    std::vector<Object*> get_obstacles() const { return obstacles; }
    std::vector<Enemy*> get_enemies() const { return enemies; }
    int get_camera_x() const { return camera_x; }
    void add_object(Object* object);
    void remove_object(Object* object);
    void add_enemy(Enemy* enemy);
    void remove_enemy(Enemy* enemy);
    void add_brick(Brick* brick);
    void remove_brick(Brick* brick);
    void add_block(Block* block);
    void set_mario(Mario* mario);
    void increment_coins();
    void increment_lives();
    Window* get_window() { return &win; }
    void on_marios_death();
    void on_win();
    void play_sound_effect(std::string filename);

private:
    void load_level(std::string level_addr);
    void clear();
    void draw_background();
    void draw();
    void handle_events();
    void update();
    void update_camera();
    void handle_object_interactions();
    void draw_banner();

    Window win;
    int camera_x;
    bool game_running;
    Mario* mario;
    int n_coins, n_lives;
    ExactRectangle marios_initial_pos;

    std::vector<Block*> blocks;
    std::vector<Brick*> bricks;
    std::vector<Enemy*> enemies;
    std::vector<Object*> obstacles;
    std::vector<Object*> objects;
};


#endif
