#include "Mario.h"
#include "AssetsAddresses.h"
#include "utility.h"
#include "Mushroom.h"
#include "Game.h"

using namespace std;

#define KEY_UP 'w'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

const double Mario::max_vx = 20;
const double Mario::max_vy = 30;
const double Mario::friction_constant = 0.12, Mario::stop_threshold = 5;
const int Mario::max_jump_time = 5;

Mario::Mario(ExactRectangle position, Game* game) :
    MovingObject(position, game), walk_index_handler(2,3) {

    motion_state = STANDING;
    direction = RIGHT;
    strength = NORMAL;

    vx = vy = ax = 0;
    ay = GRAVITATIONAL_ACCELERATION;

    immunity_counter = 0;
}

void Mario::handle_key_press(char key) {
    if (key == KEY_RIGHT) {
        if (motion_state == SLIDING)
            ax = 2;
        else
            ax = 2.5;
    } else if (key == KEY_LEFT) {
        if (motion_state == SLIDING)
            ax = -2;
        else
            ax = -2.5;
    } else if (key == KEY_UP) {
        if (motion_state != JUMPING && !jump_key_held) {
            vy = -22;
            ay = 0;
            jump_timer = max_jump_time;
            if (strength == NORMAL)
                game->play_sound_effect(JUMP_SMALL_SOUND);
            else if (strength == BIG)
                game->play_sound_effect(JUMP_SUPER_SOUND);
        }
        jump_key_held = true;
    }
}

void Mario::handle_key_release(char key) {
    if (key == KEY_RIGHT && ax >= 0) {
        ax = 0;
    } else if (key == KEY_LEFT && ax < 0) {
        ax = 0;
    } else if (key == KEY_UP) {
        jump_key_held = false;
        ay = GRAVITATIONAL_ACCELERATION;
        jump_timer = 0;
    }
}

void Mario::set_vx(double vx) {
    this->vx = closest_in_interval(vx, -max_vx, max_vx);
}

void Mario::set_vy(double vy) {
    this->vy = closest_in_interval(vy, -max_vy, max_vy);
}

void Mario::move_one_frame() {
    MovingObject::move_one_frame();
    vx = max(min(vx, max_vx), -max_vx);
    vy = max(min(vy + ay, max_vy), -max_vy);
}


void Mario::update() {
    move_one_frame_with_obstacles(game->get_obstacles());
    apply_friction();
    update_state();
    handle_jump_continuation();
    apply_screen_exit_rules();
    update_immunity_counter();
}

void Mario::update_state() {
    update_motion_state();
    update_direction();
}

void Mario::update_motion_state() {
    if (!is_touching_ground()) {
        motion_state = JUMPING;
    } else if (vx != 0) {
        if (ax * vx < 0) {
            motion_state = SLIDING;
        } else if (motion_state != WALKING) {
            motion_state = WALKING;
            walk_index_handler.reset();
        } else {
            walk_index_handler.next();
        }
    } else {
        motion_state = STANDING;
    }
}


bool Mario::is_touching_ground() {
    bool result = false;
    for (int i = 0; i < game->get_obstacles().size(); i++) {
        if (compare_floats(game->get_obstacles()[i]->get_position().y, position.y + position.h)) {
            result = true;
        }
    }
    return result;
}

void Mario::apply_friction() {
    if (ax != 0 || vx == 0)
        return;

    if (motion_state == WALKING) {
        if (vx > 0) {
            vx = max(vx - (friction_constant * vx), 0.0);
            if (vx < stop_threshold)
                vx = 0;
        }
        else if (vx < 0) {
            vx = min(vx - (friction_constant * vx), 0.0);
            if (vx > -stop_threshold)
                vx = 0;
        }
    }
}

void Mario::handle_jump_continuation() {
    if (jump_timer > 0)
        jump_timer--;
    if (jump_timer == 0 || vy == 0) {
        ay = GRAVITATIONAL_ACCELERATION;
        jump_timer = 0;
    }
}

string Mario::get_image_addr() const {
    string address = MARIO_ADDR;

    if (strength == NORMAL)
        address += "/normal";
    else if (strength == BIG)
        address += "/big";

    if (motion_state == STANDING)
        address += "/standing";
    else if (motion_state == WALKING)
        address += "/walking";
    else if (motion_state == JUMPING)
        address += "/jumping";
    else if (motion_state == SLIDING)
        address += "/sliding";

    if (direction == RIGHT)
        address += "-right";
    else if (direction == LEFT)
        address += "-left";

    if (motion_state == WALKING) {
        address+= "-" + to_string(walk_index_handler.current() + 1);
    }
    address += ".png";
    return address;
}

void Mario::reset(ExactRectangle reset_pos) {
    set_position(reset_pos);
    vx = vy = 0;
    ax = ay = 0;
}

void Mario::handle_interaction_with_object(Object *obj) {
    if (dynamic_cast<Enemy*>(obj) != NULL)
        handle_interaction_with_enemy((Enemy*)obj);
    else if (dynamic_cast<RedMushroom*>(obj) != NULL)
        handle_interaction_with_mushroom((Mushroom*)obj);
}

void Mario::handle_interaction_with_mushroom(Mushroom *mushroom) {
    if (mushroom->collides(this))
        set_strength(BIG);
}

void Mario::handle_interaction_with_enemy(Enemy* enemy) {
    Collision collision = check_collision_on_next_frame(enemy);
    if (enemy->is_dead() || collision == Collision::NO_COLLISION || immunity_counter > 0)
        return;

    KoopaTroopa* koopa_troopa = dynamic_cast<KoopaTroopa*>(enemy);
    bool upside_down_koopa_troopa = (koopa_troopa != NULL && koopa_troopa->is_upside_down());
    if (upside_down_koopa_troopa && koopa_troopa->get_vx() != 0) {
        reduce_strength();
    } else if (collision.from_top) {
        if (!upside_down_koopa_troopa)
            vy = -7;
    } else if (collision.from_right || collision.from_left || collision.from_bottom) {
        reduce_strength();
    }

}

void Mario::set_strength(Mario::Strength new_strength) {
    ExactRectangle new_position = position;
    if (this->strength == NORMAL && new_strength == BIG) {
        new_position.h = CELL_SIZE_PX * 2;
        new_position.y = position.y - CELL_SIZE_PX;
    } else if (this->strength == BIG && new_strength == NORMAL) {
        new_position.h = CELL_SIZE_PX;
        new_position.y = position.y + CELL_SIZE_PX;
    }
    set_position(new_position);
    this->strength = new_strength;
}

void Mario::reduce_strength() {
    if (strength == BIG) {
        set_strength(NORMAL);
        immunity_counter = 10;
    } else if (strength == NORMAL) {
        die();
    }
}

void Mario::die() {
    game->on_marios_death();
}

void Mario::update_immunity_counter() {
    if (immunity_counter > 0)
        immunity_counter--;
}

void Mario::apply_screen_exit_rules() {
    if (position.x < game->get_camera_x()) {
        position.x = game->get_camera_x();
        vx = 0;
    }

    if (position.y > game->get_window()->get_height())
        die();
}

