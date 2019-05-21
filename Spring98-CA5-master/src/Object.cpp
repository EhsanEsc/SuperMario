#include "Object.h"
#include "utility.h"

using namespace std;

void Object::draw(Window &win, int camera_x) {
    win.draw_img(get_image_addr(), convert_to_rectangle(get_position().relative_to_x(camera_x)));
}

bool Object::collides(Object *object) const {
    return get_position().intersects(object->get_position());
}

Object::Object(ExactRectangle _position, Game *_game) :
        position(_position), game(_game) {}

void Object::handle_interaction_with_mario(Mario* mario) {}


MovingObject::MovingObject(ExactRectangle position, Game *game) :
    Object(position, game) {
    ay = GRAVITATIONAL_ACCELERATION;
}

Collision MovingObject::check_collision_on_next_frame(const Object* o) {
    const double relative_vx = get_vx() - o->get_vx();
    const double relative_vy = get_vy() - o->get_vy();
    ExactRectangle next_pos = get_position();
    next_pos.x += relative_vx;
    next_pos.y += relative_vy;

    if (!next_pos.intersects(o->get_position()))
        return Collision::NO_COLLISION;

    ExactRectangle only_move_along_x = next_pos;
    only_move_along_x.y -= relative_vy;
    if (!only_move_along_x.intersects(o->get_position())) {
        //the collision is vertical
        return Collision(relative_vy > 0, relative_vy < 0, false, false);
    }

    ExactRectangle only_move_along_y = next_pos;
    only_move_along_y.x -= relative_vx;
    if (!only_move_along_y.intersects(o->get_position())) {
        //the collision is horizontal
        return Collision(false, false, relative_vx > 0, relative_vx < 0);
    }

    //stops colliding only if you stop movement along both axes
    return Collision(relative_vy > 0, relative_vy < 0, relative_vx > 0, relative_vx < 0);
}


Collision MovingObject::move_one_frame_with_obstacles(const std::vector<Object*>& obstacles) {

    Collision result;
    for (int i = 0; i < obstacles.size(); i++) {
        Collision collision = check_collision_on_next_frame(obstacles[i]);
        result = result.aggregate(collision);
        if (collision == Collision::NO_COLLISION)
            continue;

        ExactRectangle new_pos = get_position();
        double new_vx = get_vx(), new_vy = get_vy();
        if (collision.from_top) {
            new_pos.y = obstacles[i]->get_position().y - new_pos.h;
            new_vy = 0;
        }
        if (collision.from_bottom) {
            new_pos.y = obstacles[i]->get_position().y + obstacles[i]->get_position().h;
            new_vy = 0;
        }
        if (collision.from_left) {
            new_pos.x = obstacles[i]->get_position().x - new_pos.w;
            new_vx = 0;
        }
        if (collision.from_right) {
            new_pos.x = obstacles[i]->get_position().x + obstacles[i]->get_position().w;
            new_vx = 0;
        }

        set_position(new_pos);
        set_vx(new_vx);
        set_vy(new_vy);
    }

    move_one_frame();
    return result;
}

void MovingObject::move_one_frame() {
    position.x += vx;
    vx = vx + ax;
    position.y += vy;
    vy = vy + ay;
}


void MovingObject::update_direction() {
    if (vx > 0)
        direction = RIGHT;
    if (vx < 0)
        direction = LEFT;
}

