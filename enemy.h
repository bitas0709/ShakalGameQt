#ifndef ENEMY_H
#define ENEMY_H
#include "unit.h"


class enemy : public unit
{
public:
    enemy();
private:
    int maxUnit = 5; //максимальное количество врагов
};

#endif // ENEMY_H
