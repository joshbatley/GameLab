#include "Noise.h"

Noise::Noise()
{
    _noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    _noise.SetFrequency(0.006f);
    _noise.SetSeed(Noise::_getRandomInt());
}

void Noise::SetSeed(int seed)
{
    _noise.SetSeed(seed);
}

void Noise::SetNoiseType(FastNoiseLite::NoiseType type)
{
    _noise.SetNoiseType(type);
}

void Noise::SetRandomSeed()
{
    _noise.SetSeed(Noise::_getRandomInt());
}

float Noise::GetNoise(float x, float y)
{
    return _noise.GetNoise(x, y);
}

int Noise::_getRandomInt()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen();
}
