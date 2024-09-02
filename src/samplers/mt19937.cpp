#include <iostream>
#include <random>

#include <headers/sampler.hpp>

namespace sf{

class MersenneSampler : public Sampler {

    static std::random_device rd;
    std::mt19937_64 rng;

public:
    MersenneSampler() : rng(rd()) {}

    // Generate random doubles in the interval [initial, last)
    float random_real(float initial, float last) {
        std::uniform_real_distribution<float> distribution(initial, last);
        return distribution(rng);
    }

    // Generate random int in the interval [initial, last]
    int random_int(int initial, int last) {
        std::uniform_int_distribution<int> distribution(initial, last);
        return distribution(rng);
    }

    float next() override {
        return random_real(0, 1);
    }

    void seed(int index) override {
        rng.seed(index);
    }

    ref<Sampler> clone() const override {
        return std::make_shared<MersenneSampler>(*this);
    }

};

}