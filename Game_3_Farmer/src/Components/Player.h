#pragma once

#include <iostream>

class Player {
public:
    Player(int id);
    void Update();
private:
    int _id = 0;
};


class Player2 {
public:
    Player2(int id);
    void Update();
private:
    int _id2 = 2;
};
