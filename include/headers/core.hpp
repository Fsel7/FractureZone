#pragma once
#include <memory>

namespace sf {
template <typename T> using ref = std::shared_ptr<T>;

}