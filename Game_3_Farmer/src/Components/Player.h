#pragma once

#include <iostream>

class Player {
public:
    Player(int id);
    void Update();
private:
    int _id = 0;
};
