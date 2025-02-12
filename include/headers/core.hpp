#pragma once
#include <memory>
#include <iostream>

namespace sf {
template <typename T> using ref = std::shared_ptr<T>;


/// @brief Asserts that a given condition is fulfilled, and aborts if that is
/// note the case.
#define assert_condition(condition, message)                                   \
    if (!(condition)) {                                                        \
        std::cout << message;                                                  \
        abort();                                                               \
    }

}