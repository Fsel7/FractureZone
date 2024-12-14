#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <headers/math.hpp>
#include <headers/core.hpp>
#include <random>

#pragma once

/// @brief Mostly copied from lightwave, the Saarland University's computer graphic chair's own rendering engine,
/// which is freely distributable.

namespace sf {

class Sampler {

public:
    Sampler() {}

    /// @brief Generates a single random number in the interval [-1,1).
    virtual float next() = 0;
    /// @brief Generates a single random number in the interval [min, max).
    virtual float next(float min, float max) = 0;
    /// @brief Generates a random point in the unit square [-1,1)^2.
    Vector2f next2D() { return {next(), next()}; }
    /// @brief Generates a random point in the unit square [min, max)^2.
    Vector2f next2D(float min, float max) { return {next(min, max), next(min, max)}; }
    /// @brief Generates a random Color.
    virtual Color nextColor() = 0;

    /// @brief Initiates a random number sequence characterized by the given number.
    virtual void seed(int index) = 0;
};

    
static std::random_device rd;

class MersenneSampler : public Sampler {

public:
    MersenneSampler() : rng(rd()) {}

    Color nextColor() override {
        return {static_cast<uint8_t>(colorDistr(rng)), static_cast<uint8_t>(colorDistr(rng)), static_cast<uint8_t>(colorDistr(rng))};
    }

    float next() override { return unitDistr(rng); }

    float next(float min, float max) override { return random_real(min, max); }

    void seed(int index) override { rng.seed(index); }

private:
    std::mt19937_64 rng;
    std::uniform_real_distribution<float> unitDistr;
    std::uniform_int_distribution<int> colorDistr;

private:
    /// @brief Generate random float in the interval [initial, last)
    float random_real(float initial, float last) {
        std::uniform_real_distribution<float> distribution(initial, last);
        return distribution(rng);
    }

};

}