cmake_minimum_required(VERSION 3.16)
project(SilverThread VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(silver_thread
    src/main.cpp
    src/core/Random.cpp
    src/core/Inventory.cpp
    src/core/Player.cpp
    src/core/Game.cpp
    src/items/Items.cpp
    src/items/ItemFactory.cpp
    src/story/Requirement.cpp
    src/story/Effect.cpp
    src/story/Node.cpp
    src/story/StoryTree.cpp
    src/story/StoryBuilder.cpp
    src/characters/Characters.cpp
    src/combat/Enemy.cpp
    src/combat/CombatActions.cpp
    src/combat/Combat.cpp
    src/endings/FinalBattle.cpp
    src/ui/ConsoleView.cpp
)

target_include_directories(silver_thread PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(silver_thread PRIVATE /W4 /utf-8)
else()
    target_compile_options(silver_thread PRIVATE -Wall -Wextra -Wpedantic)
endif()