#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H

#include <vector>
#include "rsdl.hpp"
#include "ExactRectangle.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end);

Rectangle convert_to_rectangle(ExactRectangle r);

template <typename Base, typename Sub> std::vector<Base*> cast_vector_elements(std::vector<Sub*> vec) {
    std::vector<Base*> result;
    for (int i = 0; i < vec.size(); i++)
        result.push_back((Base*)vec[i]);
    return result;
}

bool compare_floats(double a, double b, double epsilon = 0.1);

template <typename T> void delete_vector(std::vector<T*> vec) {
    for (int i = 0; i < vec.size(); i++)
        delete vec[i];
}

template <typename T> int find_in_vector(std::vector<T> vec, T value) {
    for (int i = 0; i < vec.size(); i++)
        if (vec[i] == value)
            return i;
    return -1;
}

void show_text(Window& win, std::string text, Point position, int size = 24);

template <typename T> void erase(std::vector<T>& vec, T value) {
    vec.erase(vec.begin() + find_in_vector(vec, value));
}


#endif
