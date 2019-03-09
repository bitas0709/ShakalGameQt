#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"

class player : public unit
{
public:
    player();
    int time; //скорость движения игрока
private:
    qint8 score; //счёт игрока
};

#endif // PLAYER_H

