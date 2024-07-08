#pragma once


enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct Animated {
    int number;
    Direction direction;
};

struct State {
    const char *name;
    glm::ivec2 location;
    const char *filePath;
};

struct GameAsset {
    const char *name;
    glm::ivec2 size;
    glm::ivec2 location;
    const char *filePath;
};
