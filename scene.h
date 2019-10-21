#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QCoreApplication>
#include <QOpenGLShaderProgram>
#include <QObject>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QMatrix4x4>

#include "player.h"
#include "map.h"


class Scene : public QOpenGLWidget
{
Q_OBJECT
public:
    Scene( QWidget *parent = nullptr );
    ~Scene();

signals:

    void tick();
    void changePlayerTexture();

private slots:

    void gameTick();
    void moveCamera();

private:

    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    QVector<int> pressedKeys;

    QTimer* doTick;
    int tickTime = 16; //привязка к примерно 60 тикам в секунду. Фуфуфу так делать не надо, но я сделаю

    Player *m_player;
    map *m_map;
    Object *m_object[20];
    QOpenGLShaderProgram m_program;

    QMultiMap<int, float> collisionList; //список объектов, через которые игрок не сможет пройти. Добавляются только с passable: no
    QVector<int> collisionObjNumWithPlayer; //номера трёх максимально близких к игроку объектов

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;
    int m_matrixUniform;

    float matrixX = 0.0f;
    float matrixY = 0.0f;
    float matrixZ = -1.0f;

    float cameraSizeX = 50.0f;
    float cameraSizeY = 50.0f;
    bool stickCameraToThePlayer = true; //зафиксировать камеру на игроке

};



#endif // SCENE_H
