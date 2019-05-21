#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#include "AutomaticMovingObject.h"
#include "AnimationIndexHandler.h"

class Mario;

class Enemy : public AutomaticMovingObject {
public:
    Enemy(ExactRectangle position, Game* game, double speed);
    void update() override;
    virtual void handle_interaction_with_mario(Mario* mario) = 0;
    virtual void die();
    virtual void handle_interaction_with_enemy(Enemy* enemy);
    bool is_dead() const { return _is_dead; }
protected:
    bool started_moving;
    bool _is_dead;
    double speed;
};

class LittleGoomba : public Enemy {
public:
    LittleGoomba(ExactRectangle position, Game* game);
    std::string get_image_addr() const override;
    void update() override;
    void handle_interaction_with_mario(Mario* mario) override;
    void die() override;

private:
    AnimationIndexHandler animation_index_handler;
    int death_cleanup_counter;
};

class KoopaTroopa : public Enemy {
public:
    KoopaTroopa(ExactRectangle pos, Game* game);
    std::string get_image_addr() const override;
    void handle_interaction_with_mario(Mario* mario) override;
    void update() override;
    void die() override;
    bool is_upside_down() const { return _is_upside_down; }

private:
    bool _is_upside_down;
    AnimationIndexHandler animation_index_handler;
    static const double shoot_speed;
};

#endif //SRC_ENEMY_H
