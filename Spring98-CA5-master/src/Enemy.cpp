#include "Enemy.h"
#include "AssetsAddresses.h"
#include "Game.h"

using namespace std;

Enemy::Enemy(ExactRectangle position, Game *game, double speed) :
        AutomaticMovingObject(position, game) {
    vx = vy = ax = 0;
    ay = GRAVITATIONAL_ACCELERATION;
    started_moving = false;
    _is_dead = false;
    this->speed = speed;
}

void Enemy::update() {
    AutomaticMovingObject::update();
    if (game->get_camera_x() + game->get_window()->get_width() > position.x &&
        !started_moving) {
        started_moving = true;
        vx = speed;
    }
}

void Enemy::handle_interaction_with_enemy(Enemy *enemy) {
    KoopaTroopa* koopa_troopa = dynamic_cast<KoopaTroopa*>(enemy);
    if (koopa_troopa != NULL && enemy->collides(this)) {
        if (koopa_troopa->is_upside_down() && koopa_troopa->get_vx() != 0)
            this->die();
    }
}

void Enemy::die() {
    game->play_sound_effect(ENEMY_STOMP_SOUND);
}


//=================================LittleGoomba================================

LittleGoomba::LittleGoomba(ExactRectangle position, Game *game) :
        Enemy(position, game, -5), animation_index_handler(2, 2) {}

std::string LittleGoomba::get_image_addr() const {
    string img_name;
    if (_is_dead)
        img_name = "dead";
    else
        img_name = string("walking-") + to_string(animation_index_handler.current() + 1);
    return LITTLE_GOOMBA_ADDR + img_name + ".png";
}

void LittleGoomba::update() {
    Enemy::update();
    animation_index_handler.next();
    if (_is_dead) {
        death_cleanup_counter--;
        if (death_cleanup_counter <= 0)
            game->remove_enemy(this);
    }
}

void LittleGoomba::handle_interaction_with_mario(Mario* mario) {
    if (mario->is_immune())
        return;

    if (mario->check_collision_on_next_frame(this).from_top && !is_dead()) {
        die();
    }
}

void LittleGoomba::die() {
    Enemy::die();
    _is_dead = true;
    vx = vy = ax = ay = 0;
    death_cleanup_counter = 10;
}

//=================================KoopaTroopa================================
const double KoopaTroopa::shoot_speed = 40;

KoopaTroopa::KoopaTroopa(ExactRectangle pos, Game *game) :
        Enemy(pos, game, -3) , animation_index_handler(2, 2){
    _is_upside_down = false;
}

std::string KoopaTroopa::get_image_addr() const {
    string img_name;
    if (_is_upside_down)
        img_name = "upside_down";
    else
        img_name = string("walking-") + (vx > 0 ? "right-" : "left-") +
                   to_string(animation_index_handler.current() + 1);
    return KOOPA_TROOPA_ADDR + img_name + ".png";
}

void KoopaTroopa::handle_interaction_with_mario(Mario* mario) {
    Collision collision = mario->check_collision_on_next_frame(this);
    if (!collision.from_top)
        return;

    if (_is_upside_down) {
        if (vx == 0)
            vx = (mario->get_vx() >= 0 ? shoot_speed : -shoot_speed);
    } else {
        _is_upside_down = true;
        vx = 0;
    }
}


void KoopaTroopa::update() {
    Enemy::update();
    animation_index_handler.next();
}

void KoopaTroopa::die() {
    Enemy::die();
    game->remove_enemy(this);
}