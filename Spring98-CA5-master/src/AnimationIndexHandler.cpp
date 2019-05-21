#include "AnimationIndexHandler.h"

AnimationIndexHandler::AnimationIndexHandler(int n_updates_for_index_increment, int max_index) {
    this->n_updates_for_index_increment = n_updates_for_index_increment;
    this->max_index = max_index;
    reset();
}

void AnimationIndexHandler::reset() {
    update_counter = 0;
}

int AnimationIndexHandler::next() {
    update_counter++;
    return (update_counter / n_updates_for_index_increment) % max_index;
}

int AnimationIndexHandler::current() const {
    return (update_counter / n_updates_for_index_increment) % max_index;
}

