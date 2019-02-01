#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"


class player : public unit
{
public:
    player();

    qint8 score; //счёт игрока
    int time; //скорость движения игрока

};

#endif // PLAYER_H
