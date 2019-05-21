#ifndef SRC_OBJECT_H
#define SRC_OBJECT_H

#include "ExactRectangle.h"
#include "Collision.h"
#include <vector>

#define GRAVITATIONAL_ACCELERATION 6.0

class Game;
class Mario;

class Object {
public:
    Object(ExactRectangle _position, Game* _game);
    virtual ExactRectangle get_position() const { return position; }
    virtual void set_position(ExactRectangle position) { this->position = position; }
    virtual void draw(Window& win, int camera_x);
    virtual void update() = 0;
    virtual std::string get_image_addr() const = 0;
    bool collides(Object* object) const;
    virtual void handle_interaction_with_mario(Mario* mario);
    virtual double get_vx() const { return 0; }
    virtual double get_vy() const { return 0; }
protected:
    ExactRectangle position;
    Game* game;
};



class MovingObject : public Object {
public:
    MovingObject(ExactRectangle position, Game* game);
    virtual double get_vx() const { return vx; }
    virtual double get_vy() const { return vy; }
    virtual void set_vx(double vx) { this->vx = vx; }
    virtual void set_vy(double vy) { this->vy = vy; }
    Collision check_collision_on_next_frame(const Object* o);
    virtual Collision move_one_frame_with_obstacles(const std::vector<Object*>& obstacles);
    virtual void move_one_frame();
protected:
    void update_direction();

    double vx, vy;
    double ax, ay;
    enum Direction {LEFT, RIGHT} direction;
};


#endif
