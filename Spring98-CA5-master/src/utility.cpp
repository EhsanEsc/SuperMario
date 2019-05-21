#include "utility.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end) {
    if (val > interval_end)
        return interval_end;
    if (val < interval_begin)
        return interval_begin;
    return val;
}

Rectangle convert_to_rectangle(ExactRectangle r) {
    return Rectangle((int)r.x, (int)r.y, r.w, r.h);
}

bool compare_floats(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

void show_text(Window& win, std::string text, Point position, int size) {
    win.show_text(text, position, WHITE, "../assets/fonts/OpenSans.ttf", size);
}
