#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

#include "st/core/Game.hpp"
#include "st/core/Random.hpp"
#include "st/story/StoryBuilder.hpp"
#include "st/ui/ConsoleView.hpp"

int main() {
    try {
        auto view = std::make_unique<st::ConsoleView>();
        auto tree = st::StoryBuilder{}.build();
        auto random = std::make_unique<st::Random>();

        st::Game game(std::move(tree), std::move(view), std::move(random));
        game.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& error) {
        std::cerr << "Критическая ошибка: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}