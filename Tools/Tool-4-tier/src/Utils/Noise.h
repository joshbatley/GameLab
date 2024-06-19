#pragma once

#include "FastNoiseLite.h"
#include <random>

class Noise {
public:
    static Noise &getInstance()
    {
        static Noise instance;
        return instance;
    }

    void SetNoiseType(FastNoiseLite::NoiseType type);
    void SetSeed(int seed);
    void SetRandomSeed();
    float GetNoise(float x, float y);

private:
    Noise();
    Noise(Noise const &) = delete;
    void operator=(Noise const &) = delete;

    FastNoiseLite _noise;
    int _getRandomInt();
};
