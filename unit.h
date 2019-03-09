#ifndef UNIT_H
#define UNIT_H

#include <QMainWindow>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>
#include <QTimer>

//Данный класс содержит основные функции и переменные, свойственные и для игрока, и для его врага

class unit : public QGLWidget
{
public:
    unit();
    void initVertices(); //задание вершин модели юнита
    void initColors(); //задание цвета модели юнита
    void spawn(); //создание юнита на поле
    void move(); //перемещение юнита
    void draw(); //отрисовка юнита
    void death(); //смерть юнита

    std::vector<float> m_vertices;
    std::vector<float> m_colors;

    int x = 0, y = 0; //стартовые координаты модели
    int hp = 0; //очки здоровья юнита
    QTimer *timer = new QTimer(this);
protected:
    QOpenGLShaderProgram *m_program;
    int m_vertexAttr;
    int m_colorAttr;
    int m_matrixUniform;
};

#endif // UNIT_H
