#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QVector>

#include "objects.h"
#include "player.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:

    GameEngine();
    ~GameEngine();

private slots:

    void gameTick();
    void keyPressTaken( QKeyEvent *event );
    void keyReleaseTaken( QKeyEvent *event );

private:

    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    QVector<int> pressedKeys;
    void startGame();
    QTimer* doTick;
    int tickTime = 16; //привязка к примерно 60 тикам в секунду. Фуфуфу так делать не надо, но я сделаю

};

#endif // GAMEENGINE_H
