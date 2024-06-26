#pragma once

namespace Vec {
    struct vec2 {
        float x, y;

        vec2()
            : x(0.0f), y(0.0f) {}
        vec2(float X, float Y)
            : x(X), y(Y) {}
    };

    struct uvec2 {
        unsigned int x, y;

        uvec2()
            : x(0), y(0) {}
        uvec2(unsigned int X, unsigned int Y)
            : x(X), y(Y) {}
    };

    struct ivec2 {
        int x, y;

        ivec2()
            : x(0), y(0) {}
        ivec2(int X, int Y)
            : x(X), y(Y) {}
    };

    struct vec3 {
        float x, y, z;

        vec3()
            : x(0.0f), y(0.0f), z(0.0f) {}
        vec3(float X, float Y, float Z)
            : x(X), y(Y), z(Z) {}
    };

    struct uvec3 {
        unsigned int x, y, z;

        uvec3()
            : x(0), y(0), z(0) {}
        uvec3(unsigned int X, unsigned int Y, unsigned int Z)
            : x(X), y(Y), z(Z) {}
    };

    struct ivec3 {
        int x, y, z;

        ivec3()
            : x(0), y(0), z(0) {}
        ivec3(int X, int Y, int Z)
            : x(X), y(Y), z(Z) {}
    };

    struct vec4 {
        float x, y, z, w;

        vec4()
            : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        vec4(float X, float Y, float Z, float W)
            : x(X), y(Y), z(Z), w(W) {}
    };

    struct uvec4 {
        unsigned int x, y, z, w;

        uvec4()
            : x(0), y(0), z(0), w(0) {}
        uvec4(unsigned int X, unsigned int Y, unsigned int Z, unsigned int W)
            : x(X), y(Y), z(Z), w(W) {}
    };

    struct ivec4 {
        int x, y, z, w;

        ivec4()
            : x(0), y(0), z(0), w(0) {}
        ivec4(int X, int Y, int Z, int W)
            : x(X), y(Y), z(Z), w(W) {}
    };

    struct color : public ivec4 {
        color(int r, int g, int b, int a)
        {
            x = r;
            y = g;
            z = b;
            w = a;
        }
    };
}
