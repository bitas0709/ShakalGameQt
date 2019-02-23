#include "player.h"

player::player( QOpenGLShaderProgram *program, int vertexAttr, int colorAttr )
{
    hp = 100; //уровень здоровья игрока
    score = 0; //стартовые очки
    time = 500; //скорость перемещения игрока (в миллисекундах)
}
