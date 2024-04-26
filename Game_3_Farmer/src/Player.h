#pragma once

#include <iostream>
#include "Entity.h"

class Player {
public:
    Player(int id);
    void Update();
private:
    int _id = 0;
};
