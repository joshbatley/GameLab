#pragma once

namespace utils {
    // 2-Component Vectors
    struct vec2 {
        float x, y;

        vec2() : x(0.0f), y(0.0f) {}
        vec2(float newX, float newY) : x(newX), y(newY) {}
    };

    struct uvec2 {
        unsigned int x, y;

        uvec2() : x(0), y(0) {}
        uvec2(unsigned int newX, unsigned int newY) : x(newX), y(newY) {}
    };

    struct ivec2 {
        int x, y;

        ivec2() : x(0), y(0) {}
        ivec2(int newX, int newY) : x(newX), y(newY) {}
    };

    // 3-Component Vectors
    struct vec3 {
        float x, y, z;

        vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        vec3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
    };

    struct uvec3 {
        unsigned int x, y, z;

        uvec3() : x(0), y(0), z(0) {}
        uvec3(unsigned int newX, unsigned int newY, unsigned int newZ) : x(newX), y(newY), z(newZ) {}
    };

    struct ivec3 {
        int x, y, z;

        ivec3() : x(0), y(0), z(0) {}
        ivec3(int newX, int newY, int newZ) : x(newX), y(newY), z(newZ) {}
    };

    // 4-Component Vectors
    struct vec4 {
        float x, y, z, w;

        vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        vec4(float newX, float newY, float newZ, float newW) : x(newX), y(newY), z(newZ), w(newW) {}
    };

    struct uvec4 {
        unsigned int x, y, z, w;

        uvec4() : x(0), y(0), z(0), w(0) {}
        uvec4(unsigned int newX, unsigned int newY, unsigned int newZ, unsigned int newW) : x(newX), y(newY), z(newZ), w(newW) {}
    };

    struct ivec4 {
        int x, y, z, w;

        ivec4() : x(0), y(0), z(0), w(0) {}
        ivec4(int newX, int newY, int newZ, int newW) : x(newX), y(newY), z(newZ), w(newW) {}
    };

}
