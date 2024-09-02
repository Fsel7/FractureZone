#include <random>
#include <headers/sampler.hpp>

namespace sf{

static std::random_device rd;

class MersenneSampler : public Sampler {

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

    Color nextColor() override {
        return {static_cast<Uint8>(random_int(0, 255)), static_cast<Uint8>(random_int(0, 255)), static_cast<Uint8>(random_int(0, 255))};
    }

    float next() override {
        return random_real(-1, 1);
    }

    void seed(int index) override {
        rng.seed(index);
    }

    ref<Sampler> clone() const override {
        return std::make_shared<MersenneSampler>(*this);
    }

};

}