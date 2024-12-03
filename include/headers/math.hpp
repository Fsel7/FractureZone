#include <SFML/System/Vector2.hpp>
#include <cmath>

#pragma once

namespace sf {

    inline float sqr(int r){
        return 1.f * r * r;
    }

    inline float sqr(float r){
        return r * r;
    }

    inline Vector2f normalized(Vector2i target) {
        const float norm = sqrt(sqr(target.x) + sqr(target.y));
        if (norm == 0)
            return Vector2f(0, 0);
        return Vector2f(target.x / norm, target.y / norm);
    }

    inline Vector2f normalized(Vector2f target) {
        const float norm = sqrt(sqr(target.x) + sqr(target.y));
        if (norm == 0)
            return Vector2f(0, 0);
        return Vector2f(target.x / norm, target.y / norm);
    }

    inline float length(Vector2f target) {
        const float norm = sqr(target.x) + sqr(target.y);
        return std::sqrt(norm);
    }

    inline float fractionalPart(float r) {
        long long floor = (long long) r;
        return r - floor;
    }

    template<typename T>
    inline T clamp(const T value, const T lower, const T upper) {
        if (value < lower)
            return lower;
        if (value > upper)
            return upper;
        return value;
    }

    template<typename T>
    inline T lerp(const T t, const T start, const T end) {
        return t * start + (1-t) * end;
    }

}