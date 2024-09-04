#include <mygame.hpp>

constexpr int seed = 42;

int main() {
    // Add some multithreading in later on, if possible.
    // May need some OS checks later on, see lightwave.
    sf::GameEngine engine(seed);

    engine.execute();

    return 0;
}


