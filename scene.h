#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QMatrix4x4>
#include "player.h"
#include "map.h"


class Scene : public QOpenGLWidget
{
public:
    Scene( QWidget *parent = nullptr );
    ~Scene();

private slots:

    void tick();

private:

    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    QVector<int> pressedKeys;
    QTimer* doTick;
    int tickTime = 16; //привязка к примерно 60 тикам в секунду. Фуфуфу так делать не надо


    QTimer *movementTimer;
    int movementTime;
    bool canMove = true;
    void movePlayer();

    Player *m_player;
    map *m_map;
    Object *m_object[20];
    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;
    int m_matrixUniform;

    float matrixX = 0.0f;
    float matrixY = 0.0f;
    float matrixZ = -1.0f;
};

#endif // SCENE_H
