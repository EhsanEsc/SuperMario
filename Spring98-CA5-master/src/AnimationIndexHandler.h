#ifndef SRC_ANIMATIONINDEXHANDLER_H
#define SRC_ANIMATIONINDEXHANDLER_H

class AnimationIndexHandler {
public:
    AnimationIndexHandler(int n_updates_for_index_increment, int max_index);
    void reset();
    int next();
    int current() const;
private:
    int update_counter, max_index, n_updates_for_index_increment;
};

#endif //SRC_ANIMATIONINDEXHANDLER_H
