#ifndef UNIT_H
#define UNIT_H

#include <QMainWindow>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>
#include <QTimer>

//Данный класс содержит основные функции и переменные, свойственные и для игрока, и для его врага

class unit
{
public:
    unit();

    void spawn(); //создание юнита на поле
    void move(); //перемещение юнита
    void death(); //смерть юнита

    int x = 0, y = 0; //стартовые координаты модели
    int hp = 0; //очки здоровья юнита
    //QTimer *timer = new QTimer(this);
protected:

};

#endif // UNIT_H
