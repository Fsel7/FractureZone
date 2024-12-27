#include <SFML/System/Vector2.hpp>
#include <cmath>

#pragma once

namespace sf {

    inline float sqr(const int r){
        return static_cast<float>(r * r);
    }

    inline float sqr(const float r){
        return r * r;
    }

    inline Vector2f normalized(const Vector2i target) {
        const float norm = sqrt(sqr(target.x) + sqr(target.y));
        if (norm == 0)
            return Vector2f(0, 0);
        return Vector2f(target.x / norm, target.y / norm);
    }

    inline Vector2f normalized(const Vector2f target) {
        const float norm = sqrt(sqr(target.x) + sqr(target.y));
        if (norm == 0)
            return Vector2f(0, 0);
        return Vector2f(target.x / norm, target.y / norm);
    }

    inline float length(const Vector2f target) {
        const float norm = sqr(target.x) + sqr(target.y);
        return std::sqrt(norm);
    }

    inline float fractionalPart(float r) {
        // return std::fmodf(r, 1.f); // Apparently, fmodf isn't part of std on some platforms / compilers.
        float integerPart;
        return std::modf(r, &integerPart);
    }

}