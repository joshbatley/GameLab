#pragma once

class TimeManager {
public:
    TimeManager();
    void Update(unsigned int currentFrameTime);
    void Pause();
    void Resume();
    float getDeltaTime() const;

private:
    float _deltaTime;
    unsigned int _lastFrameTime;
    bool _isPaused;
};
