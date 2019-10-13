#include "gameengine.h"

GameEngine::GameEngine()
{

}

void GameEngine::gameTick() {

}

void GameEngine::startGame() {
    doTick = new QTimer();
    connect(doTick, SIGNAL(timeout()), SLOT(gameTick()));
    doTick->start(tickTime);
}

void GameEngine::keyPressEvent(QKeyEvent *event) {
    //const float step = 0.1f;
    if(!event->isAutoRepeat()) {
        switch(event->key()) {
        case Qt::Key_A:
            pressedKeys.push_back(Qt::Key_A);
            break;
        case Qt::Key_D:
            pressedKeys.push_back(Qt::Key_D);
            break;
        case Qt::Key_E:
            pressedKeys.push_back(Qt::Key_E);
            break;
        case Qt::Key_Q:
            pressedKeys.push_back(Qt::Key_Q);
            break;
        case Qt::Key_R:
            pressedKeys.push_back(Qt::Key_R);
            break;
        case Qt::Key_S:
            pressedKeys.push_back(Qt::Key_S);
            break;
        case Qt::Key_W:
            pressedKeys.push_back(Qt::Key_W);
            break;
        case Qt::Key_Down:
            pressedKeys.push_back(Qt::Key_Down);
            //m_player->setY0( m_player->y0() - step);
            break;
        case Qt::Key_Left:
            pressedKeys.push_back(Qt::Key_Left);
            //m_player->setX0( m_player->x0() - step);
            break;
        case Qt::Key_Right:
            pressedKeys.push_back(Qt::Key_Right);
            //m_player->setX0( m_player->x0() + step);
            break;
        case Qt::Key_Up:
            pressedKeys.push_back(Qt::Key_Up);
            //m_player->setY0( m_player->y0() + step);
            break;
        }
        qDebug() << pressedKeys;
    }
}

void GameEngine::keyReleaseEvent(QKeyEvent *event) {
    if(!event->isAutoRepeat()) {
        switch(event->key()) {
        case Qt::Key_A:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_A) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_D:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_D) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_E:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_E) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_Q:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Q) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_R:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_R) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_S:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_S) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_W:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_W) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_Down:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Down) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_Left:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Left) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_Right:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Right) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        case Qt::Key_Up:
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Up) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        }
        qDebug() << pressedKeys;
    }
}

void GameEngine::keyPressTaken( QKeyEvent *event ) {
    keyPressEvent( event );
}

void GameEngine::keyReleaseTaken( QKeyEvent *event ) {
    keyReleaseEvent( event );
}

GameEngine::~GameEngine() {

}
