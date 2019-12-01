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
#include <QPainter>
#include <QtGlobal>

#include "player.h"
#include "enemy.h"
#include "map.h"


class Scene : public QOpenGLWidget
{
Q_OBJECT
public:
    Scene( QWidget *parent = nullptr );
    ~Scene();

    //направление "вниз" указывать не надо, так как оно будет проверяться в любом случае
    enum MoveDirection {
        Up, Down, Left, Right
    };

    enum GameModeState {
        Single, Multiplayer
    };

signals:

    void startGame();
    void tick();
    void changePlayerTexture();
    void enableChunkLinesSignal();

private slots:

    void startGameSlot();
    void gameTick();
    void moveCamera();
    void enableChunkLines();

    void checkCollision(MoveDirection, float leftX, float rightX, float bottomY, float topY);

private:

    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    QVector<int> pressedKeys;

    QTimer* doTick;
    int tickTime = 16; //привязка к примерно 60 тикам в секунду. Фуфуфу так делать не надо, но я сделаю
    //по умолчанию 16

    QVector<int> playerChunkNum; //номер чанка, в котором находится игрок
    //int objUnderPlayer; //номер объекта, находящегося под игроком
    bool enableChunkLinesBool = false;

    float highestPointObj = 0.0f;
    QVector<int> objectsAbovePlayer;

    int GameMode = GameModeState::Single; //убрать, когда появится мультиплеер
    Player *m_player[4];
    Enemy *m_enemy[10];
    map *m_map;
    Object *m_object[2000];
    QOpenGLShaderProgram m_program;

    QVector<int> activePlayers;
    QVector<int> activeEnemies;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;
    int m_matrixUniform;

    float matrixX = 0.0f;
    float matrixY = 0.0f;
    float matrixZ = -1.0f;
    const float step = 0.1f;

    float cameraSizeX = 50.0f;
    float cameraSizeY = 50.0f;
    bool stickCameraToThePlayer = true; //зафиксировать камеру на игроке
};



#endif // SCENE_H
