#include <SFML/System/Vector2.hpp>
#include <cmath>

#pragma once

namespace sf {

    inline float sqr(float r){
        return r * r;
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

}