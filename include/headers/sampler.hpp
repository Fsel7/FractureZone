#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <headers/math.hpp>
#include <headers/core.hpp>


/// @brief Mostly copied from lightwave, the Saarland University's computer graphic chair's own rendering engine,
/// which is freely distributable.

namespace sf {

    class Sampler {
    protected:
        int m_samplesPerPixel;

    public:
        Sampler() : m_samplesPerPixel(0) {}


        /// @brief Generates a single random number in the interval [0,1).
        virtual float next() = 0;
        /// @brief Generates a random point in the unit square [0,1)^2.
        virtual Vector2f next2D() { return {next(), next()}; }
        /// @brief Generates a random point in the unit cube [0,1)^3.
        virtual Vector3f next3D() { return {next(), next(), next()}; }
        /// @brief Generates a random Color.
        virtual Color nextColor() = 0;

        /**
         * @brief Initiates a random number sequence characterized by the given
         * number.
         * @note When identical samplers are given the same seed, they are expected
         * to produce the same sequence of random numbers. For different seeds, they
         * are expected to give different random sequences.
         */
        virtual void seed(int index) = 0;
        /// @brief Returns an identical copy of the sampler, e.g., for use in
        /// different threads.
        virtual ref<Sampler> clone() const = 0;

        /// @brief Returns the number of samples that should be taken per pixel.
        int samplesPerPixel() const { return m_samplesPerPixel; }
    };
}