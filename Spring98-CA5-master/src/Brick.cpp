#include "Brick.h"
#include "AssetsAddresses.h"
#include "Game.h"
#include "Coin.h"
#include "Mushroom.h"

using namespace std;

const double Brick::bump_speed = 2.5;

Brick::Brick(ExactRectangle position, Game* game) :
    Object(position, game) {
    vy = 0;
    original_y = position.y;
}

void Brick::handle_interaction_with_mario(Mario* mario) {
    if (!mario->check_collision_on_next_frame(this).from_bottom)
        return;

    vy = -bump_speed;

    vector<Enemy*> enemies = game->get_enemies();
    for (int i = 0; i < enemies.size(); i++) {
        ExactRectangle above_brick = get_position();
        above_brick.y -= CELL_SIZE_PX;
        if (enemies[i]->get_position().intersects(above_brick))
            enemies[i]->die();
    }
}

void Brick::update() {
    position.y += vy;
    if (original_y - position.y >= 5) {
        vy = bump_speed;
    } else if (position.y > original_y) {
        vy = 0;
        position.y = original_y;
    }
}

//===============================RegularBrick===============================

string RegularBrick::get_image_addr() const {
    return REGULAR_BRICK_ADDR;
}

void RegularBrick::handle_interaction_with_mario(Mario *mario) {
    Brick::handle_interaction_with_mario(mario);

    if (mario->check_collision_on_next_frame(this).from_bottom &&
        mario->get_strength() == Mario::BIG) {
        game->play_sound_effect(BRICK_SMASH_SOUND);
        game->remove_brick(this);
    }
}


//===============================QuestionBrick===============================
QuestionBrick::QuestionBrick(ExactRectangle position, Game* game, BrickContent content) :
    Brick(position, game), animation_index_handler(2, 3) {
    is_empty = false;
    this->content = content;
}

void QuestionBrick::update() {
    Brick::update();
    animation_index_handler.next();
}

string QuestionBrick::get_image_addr() const {
    if (is_empty)
        return QUESTION_BRICK_ADDR "question-empty.png";
    else
        return  string(QUESTION_BRICK_ADDR) + "question-" +
                to_string(animation_index_handler.current() + 1) + ".png";
}

void QuestionBrick::handle_interaction_with_mario(Mario* mario) {
    Brick::handle_interaction_with_mario(mario);

    if (!mario->check_collision_on_next_frame(this).from_bottom || is_empty)
        return;

    is_empty = true;
    ExactRectangle content_spawn_position = position;
    content_spawn_position.y -= CELL_SIZE_PX;

    if (content == COIN) {
        game->add_object(new Coin(content_spawn_position, game));
        game->increment_coins();
        game->play_sound_effect(COIN_SOUND);
    } else if (content == RED_MUSHROOM) {
        game->add_object(new RedMushroom(content_spawn_position, game));
        game->play_sound_effect(RED_MUSHROOM_APPEARS_SOUND);
    } else if (content == HEALTH_MUSHROOM) {
      game->add_object(new HealthMushroom(content_spawn_position, game));
    }
}


