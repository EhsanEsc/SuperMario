#include "Game.h"
#include "utility.h"
#include "PipeBlock.h"
#include "MapReader.h"
#include <fstream>

using namespace std;

Game::Game() : win(800, 480) {
    camera_x = 0;
    n_coins = 0;
    n_lives = 3;
}

void Game::run_level(std::string level_addr) {
    load_level(level_addr);
    win.play_music(BACKGROUND_MUSIC);
    game_running = true;

    while(game_running) {
        handle_events();
        update();
        draw();

        delay(90);
    }
}

void Game::draw_background() {

    const int bg_width = 2000, bg_height = 1000;
    const int bg_x = camera_x % bg_width;
    const int bg_y = bg_height - win.get_height();

    bool reached_end = camera_x % bg_width + win.get_width() >= bg_height;

    if (!reached_end) {
        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(0, 0, win.get_width(), win.get_height()),
                Rectangle(bg_x, bg_y, win.get_width(), win.get_height())
        );
    } else {
        int first_part_width = bg_width - bg_x;
        int second_part_width = win.get_width() - first_part_width;
        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(0, 0, first_part_width, win.get_height()),
                Rectangle(bg_x, bg_y, first_part_width, win.get_height())
        );

        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(first_part_width, 0, second_part_width, win.get_height()),
                Rectangle(0, bg_y, second_part_width, win.get_height())
        );
    }
}

void Game::load_level(string level_addr) {
    clear();
    MapReader::get_instance()->read(level_addr, this);
}

void Game::draw() {
    draw_background();
    for (int i = 0; i < objects.size(); i++)
        objects[i]->draw(win, camera_x);
    draw_banner();
    win.update_screen();
}

Game::~Game() {
    delete_vector(objects);
}

void Game::handle_events() {
    while (win.has_pending_event()) {
        Event e = win.poll_for_event();
        switch (e.get_type()) {
            case Event::KEY_PRESS:
                mario->handle_key_press(e.get_pressed_key());
                break;
            case Event::KEY_RELEASE:
                mario->handle_key_release(e.get_pressed_key());
                break;
            case Event::QUIT:
                game_running = false;
                break;
        }
    }
}

void Game::update() {
    handle_object_interactions();
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->update();
    }
    update_camera();
}

void Game::add_block(Block* block) {
    blocks.push_back(block);
    obstacles.push_back(block);
    objects.push_back(block);
}

void Game::add_brick(Brick* brick) {
    bricks.push_back(brick);
    obstacles.push_back(brick);
    objects.push_back(brick);
}

void Game::remove_brick(Brick *brick) {
    erase(bricks, brick);
    erase(obstacles, (Object*)brick);
    remove_object(brick);
}

void Game::set_mario(Mario *mario) {
    this->mario = mario;
    objects.push_back(mario);
    marios_initial_pos = mario->get_position();
}

void Game::update_camera() {
    if (mario->get_position().x >  camera_x + (win.get_width() / 2)) {
        camera_x = mario->get_position().x - (win.get_width() / 2);
    }
}

void Game::handle_object_interactions() {
    Mario* unchanged_mario = new Mario(*mario);
    for (int i = 0; i < objects.size(); i++) {
        mario->handle_interaction_with_object(objects[i]);
        objects[i]->handle_interaction_with_mario(unchanged_mario);
    }
    delete unchanged_mario;

    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (i == j) continue;
            enemies[i]->handle_interaction_with_enemy(enemies[j]);
        }
    }

}

void Game::remove_object(Object* object) {
    erase(objects, object);
    delete object;
}

void Game::add_object(Object *object) {
    objects.push_back(object);
}

void Game::increment_coins() {
    n_coins++;
}

void Game::draw_banner() {
    show_text(win, "COINS", Point(win.get_width()/3 - 50, 10));
    show_text(win, to_string(n_coins), Point(win.get_width()/3 - 20, 40));
    show_text(win, "LIVES", Point(win.get_width()*2/3 - 50, 10));
    show_text(win, to_string(n_lives), Point(win.get_width()*2/3 - 25, 40));
}

void Game::add_enemy(Enemy *enemy) {
    enemies.push_back(enemy);
    objects.push_back((Object*)enemy);
}

void Game::remove_enemy(Enemy *enemy) {
    erase(enemies, enemy);
    erase(objects, (Object*)enemy);
}

void Game::on_marios_death() {
    if (n_lives > 1) {
        n_lives--;
        win.stop_music();
        play_sound_effect(MARIOS_DEATH_SOUND);
        delay(3000);
        win.play_music(BACKGROUND_MUSIC);
        camera_x = 0;
        mario->reset(marios_initial_pos);
    } else {
        win.fill_rect(Rectangle(0, 0, win.get_width(), win.get_height()), BLACK);
        show_text(win, "YOU LOSE!", Point(win.get_width()/2 - 80, win.get_height()/2 - 30), 40);
        win.update_screen();
        game_running = false;
        win.stop_music();
        play_sound_effect(GAMEOVER_SOUND);
        delay(4500);
    }

}

void Game::on_win() {
    if (!game_running)
        return;;

    win.fill_rect(Rectangle(0, 0, win.get_width(), win.get_height()), BLACK);
    show_text(win, "YOU WIN!", Point(win.get_width()/2 - 80, win.get_height()/2 - 30), 40);
    win.update_screen();
    game_running = false;
    win.stop_music();
    play_sound_effect(LEVEL_CLEAR_SOUND);
    delay(6500);
}

void Game::increment_lives() {
    n_lives++;
}

void Game::play_sound_effect(std::string filename) {
    win.play_sound_effect(filename);
}

void Game::clear() {
    delete_vector(objects);
    mario = NULL;
    blocks.clear();
    bricks.clear();
    enemies.clear();
    obstacles.clear();
    objects.clear();
}
