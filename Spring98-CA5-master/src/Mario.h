#ifndef SRC_MARIO_H
#define SRC_MARIO_H

#include "Object.h"
#include "AnimationIndexHandler.h"
#include <string>

class Game;
class Enemy;
class Mushroom;

class Mario : public MovingObject {
public:
    Mario(ExactRectangle position, Game* game);
    std::string get_image_addr() const override;
    void handle_key_press(char key);
    void handle_key_release(char key);
    void set_vx(double vx) override;
    void set_vy(double vy) override;
    virtual void update();
    void handle_interaction_with_object(Object* obj);
    void reset(ExactRectangle reset_pos);
    bool is_immune() const { return immunity_counter > 0; }
    enum MotionState {STANDING, WALKING, JUMPING, SLIDING};
    enum Strength {NORMAL, BIG};
    Strength get_strength() const { return strength; }

private:
    virtual void move_one_frame();
    void update_state();
    bool is_touching_ground();
    void apply_friction();
    void handle_jump_continuation();
    void handle_interaction_with_enemy(Enemy* enemy);
    void handle_interaction_with_mushroom(Mushroom* mushroom);
    void reduce_strength();
    void update_immunity_counter();
    void update_motion_state();
    void apply_screen_exit_rules();
    void die();

    MotionState motion_state;
    Strength strength;

    void set_strength(Strength strength);

    int jump_timer;
    bool jump_key_held;
    AnimationIndexHandler walk_index_handler;
    int immunity_counter;

    static const double max_vx, max_vy;
    static const double friction_constant, stop_threshold;
    static const int walking_counter_divider, n_walking_frames;
    static const int max_jump_time;

};


#endif 
