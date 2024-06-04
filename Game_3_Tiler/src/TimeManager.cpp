#include "TimeManager.h"

TimeManager::TimeManager(): _deltaTime(0.0f), _lastFrameTime(0), _isPaused(false) {}

void TimeManager::Update(unsigned int currentFrameTime)
{
    if (!_isPaused) {
            unsigned int deltaTicks = currentFrameTime - _lastFrameTime;
            _deltaTime = static_cast<float>(deltaTicks) / 1000.0f;
    }
    _lastFrameTime = currentFrameTime;
}

void TimeManager::Pause()
{
    _isPaused = true;
}

void TimeManager::Resume()
{
    _isPaused = false;
}

float TimeManager::getDeltaTime() const
{
    return _deltaTime;
}
