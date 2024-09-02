#include <chrono>

#pragma once

using namespace std::chrono;
struct Timer {

private:
    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();

    float deltaTime = 0;

public:
    void update() {
        tlast = tcur;
        tcur = high_resolution_clock::now();
        duration<float, std::milli> time_span = tcur - tlast;
        deltaTime = time_span.count() / 1000;
    }

    float getDeltaTime() {
        return deltaTime;
    }
};