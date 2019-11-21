#include "scene.h"

#define ObjType 0
#define ObjSizeX 1
#define ObjSizeY 2
#define ObjStartX 3
#define ObjStartY 4
#define ObjCoordZ 5
#define ObjPassable 6
#define ObjTexture 7
#define ObjNumber 8

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent )
{
    this->setFocusPolicy( Qt::StrongFocus );
    doTick = new QTimer();
}

Scene::~Scene()
{
    makeCurrent();
    //delete m_player;
    for (int i = 0; i < m_map->numObjects; i++) {
        delete m_object[i];
    }
    doneCurrent();
}

void Scene::gameTick() {
    if (GameMode == GameModeState::Single) {
        if (pressedKeys.size() != 0) {
            for (int i = 0; i < pressedKeys.size(); i++) {
                if (pressedKeys[i] == Qt::Key_Left) {
                    m_player[0]->CurrentLineOfSightPlayer = m_player[0]->EnumLineOfSightPlayer::LookLeft;
                    emit changePlayerTexture();
                    this->sender()->setObjectName("Player0");
                    emit checkCollision(MoveDirection::Left, m_player[0]->leftX0(), m_player[0]->rightX0(),
                            m_player[0]->bottomY0(), m_player[0]->topY0());
                }
            }
        }
    }
    /*qDebug() << "playerCoordY =" << m_player->bottomY0();
    if (!m_player->isPlayerJump) {
        if (m_player->bottomY0() > highestPointObj) {
            m_player->isPlayerOnGround = false;
        } else {
            m_player->isPlayerOnGround = true;
        }
    }
    if (!m_player->isPlayerOnGround) {
        //emit m_player->jumpButtonPressed(step);
        moveCamera();
        if (!m_player->isPlayerJump) {
            if (m_player->bottomY0() > 0) {
                m_player->setY0(m_player->bottomY0() - step);
            }
        }
    }
    if (pressedKeys.size() != 0) {
        for (int i = 0; i < pressedKeys.size(); i++) {
            if (pressedKeys[i] == Qt::Key_Left) {
                QVector<int> numObjects; //номера объектов в двух чанках

                if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) == qCeil(qreal(m_player->rightX0() / m_map->chunkSize))) {
                    if (playerChunkNum.size() == 1) {
                        if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) != playerChunkNum.at(0)) {
                            emit playerChangedChunkSignal();
                        }
                    } else if (playerChunkNum.size() == 2) {
                        emit playerChangedChunkSignal();
                    }
                } else {
                    if (playerChunkNum.size() == 1) {
                        emit playerChangedChunkSignal();
                    } else if (playerChunkNum.size() == 2) {
                        if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) != playerChunkNum.at(0) || qCeil(qreal(m_player->rightX0() / m_map->chunkSize)) != playerChunkNum.at(1)) {
                            emit playerChangedChunkSignal();
                        }
                    }
                }

                emit checkPlayerCollisionSignal();

                if (playerChunkNum.at(0) > 0) {
                    for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                        //получение номеров объектов в чанке, в котором находится игрок
                        if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                            numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                        }
                    }
                    for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0) - 1].size(); j++) {
                        //получение номеров объектов в левом от игрока чанке
                        if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0) - 1].at(j))) {
                            numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0) - 1].at(j));
                        }
                    }
                } else if (playerChunkNum.at(0) == 0) {
                    for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                        //получение номеров объектов в чанке, в котором находится игрок
                        if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                            numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                        }
                    }
                }
                //qDebug() << "numObjects =" << numObjects;
                bool playerCanRun = true;
                for (int i = 0; i < numObjects.size(); i++) {
                    if (qFuzzyCompare(m_player->leftX0(), m_map->ObjectData[numObjects.at(i)].at(3).toFloat()
                                      + m_map->ObjectData[numObjects.at(i)].at(1).toFloat())) {
                        if (m_player->topY0() >= m_map->ObjectData[numObjects.at(i)].at(4).toFloat() &&
                                m_player->bottomY0() < m_map->ObjectData[numObjects.at(i)].at(4).toFloat() +
                                m_map->ObjectData[numObjects.at(i)].at(2).toFloat()) {
                            //если голова выше нижней точки объекта и ноги ниже верхней точки объекта
                            playerCanRun = false;
                        }
                    }
                }
                if (playerCanRun) {
                    if (m_player->leftX0() > m_map->minX) {
                        m_player->setX0( m_player->leftX0() - step);
                    }
                }
                if (stickCameraToThePlayer) {
                    moveCamera();
                }
                if (m_player->CurrentLineOfSightPlayer == m_player->LookRight) {
                    m_player->CurrentLineOfSightPlayer = m_player->LookLeft;
                    emit changePlayerTexture();
                }
            } else if (pressedKeys[i] == Qt::Key_Right) {
                QVector<int> numObjects; //номера объектов в двух чанках

                if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) == qCeil(qreal(m_player->rightX0() / m_map->chunkSize))) {
                    if (playerChunkNum.size() == 1) {
                        if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) != playerChunkNum.at(0)) {
                            emit playerChangedChunkSignal();
                        }
                    } else if (playerChunkNum.size() == 2) {
                        emit playerChangedChunkSignal();
                    }
                } else {
                    if (playerChunkNum.size() == 1) {
                        emit playerChangedChunkSignal();
                    } else if (playerChunkNum.size() == 2) {
                        if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) != playerChunkNum.at(0) || qCeil(qreal(m_player->rightX0() / m_map->chunkSize)) != playerChunkNum.at(1)) {
                            emit playerChangedChunkSignal();
                        }
                    }
                }

                emit checkPlayerCollisionSignal();

                if (playerChunkNum.size() == 1) {
                    if (playerChunkNum.at(0) < m_map->countChunks) {
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                            //получение номеров объектов в чанке, в котором находится игрок
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                            }
                        }
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0) + 1].size(); j++) {
                            //получение номеров объектов в правом от игрока чанке
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0) + 1].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0) + 1].at(j));
                            }
                        }
                    } else {
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                            //получение номеров объектов в чанке, в котором находится игрок
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                            }
                        }
                    }
                } else if (playerChunkNum.size() == 2) {
                    if (playerChunkNum.at(1) < m_map->countChunks) {
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                            //получение номеров объектов в чанке, в котором находится игрок
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                            }
                        }
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0) + 1].size(); j++) {
                            //получение номеров объектов в правом от игрока чанке
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0) + 1].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0) + 1].at(j));
                            }
                        }
                    } else {
                        for (int j = 0; j < m_map->ChunkList[playerChunkNum.at(0)].size(); j++) {
                            //получение номеров объектов в чанке, в котором находится игрок
                            if (!numObjects.contains(m_map->ChunkList[playerChunkNum.at(0)].at(j))) {
                                numObjects.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(j));
                            }
                        }
                    }
                }
                //qDebug() << "numObjects =" << numObjects;
                bool playerCanRun = true;
                for (int i = 0; i < numObjects.size(); i++) {
                    if (qFuzzyCompare(m_player->rightX0(), m_map->ObjectData[numObjects.at(i)].at(3).toFloat())) {
                        if (m_player->topY0() >= m_map->ObjectData[numObjects.at(i)].at(4).toFloat() &&
                                m_player->bottomY0() < m_map->ObjectData[numObjects.at(i)].at(4).toFloat() +
                                m_map->ObjectData[numObjects.at(i)].at(2).toFloat()) {
                            //если голова выше нижней точки объекта и ноги ниже верхней точки объекта
                            playerCanRun = false;
                        }
                    }
                }
                if (playerCanRun) {
                    if (m_player->rightX0() < m_map->maxX) {
                        m_player->setX0( m_player->leftX0() + step);
                    }
                }
                //m_player->setX0( m_player->leftX0() + step );
                if (stickCameraToThePlayer) {
                    moveCamera();
                }
                if (m_player->CurrentLineOfSightPlayer == m_player->LookLeft) {
                    m_player->CurrentLineOfSightPlayer = m_player->LookRight;
                    emit changePlayerTexture();
                }
            } else if (pressedKeys[i] == Qt::Key_Space) {
                emit m_player->checkColl(m_player->MoveDirection::Left, m_player->leftX0(), m_player->rightX0(), m_player->bottomY0(), m_player->topY0());
                if (m_player->isPlayerOnGround) {
                    //m_player->setY0(m_player->bottomY0() + step);
                    if (!m_player->isPlayerJump) {
                        m_player->playerCoordBeforeJump = m_player->bottomY0();
                    }
                    m_player->isPlayerJump = true;
                    emit m_player->jumpButtonPressed(step);
                }
                moveCamera();
            } else if (pressedKeys[i] == Qt::Key_Down) {
                //m_player->setY0(m_player->bottomY0() - step);
                moveCamera();
            } else if (pressedKeys[i] == Qt::Key_Up) {
                m_player->setY0(m_player->bottomY0() + step);
                moveCamera();
            }
        }
    }
    //qDebug() << "NumObject =" << CurrentObjNumPlayer.at(0);*/
    update();
}

void Scene::playerChangedChunk() {
    /*if (qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) == qCeil(qreal(m_player->rightX0() / m_map->chunkSize))) {
        if (playerChunkNum.size() == 1) {
            if (playerChunkNum.at(0) != qCeil(qreal(m_player->leftX0() / m_map->chunkSize))) {
                playerChunkNum.remove(0);
                playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
            }
        } else if (playerChunkNum.size() == 2) {
            playerChunkNum.clear();
            playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
        } else if (playerChunkNum.size() == 0) {
            playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
        } else {
            qDebug() << "Something wrong, I can feel it";
        }
    } else {
        if (playerChunkNum.size() == 1) {
            playerChunkNum.clear();
            playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
            playerChunkNum.push_back(qCeil(qreal(m_player->rightX0() / m_map->chunkSize)));
        } else if (playerChunkNum.size() == 2) {
            if (playerChunkNum.at(0) != qCeil(qreal(m_player->leftX0() / m_map->chunkSize)) &&
                    playerChunkNum.at(1) != qCeil(qreal(m_player->rightX0() / m_map->chunkSize))) {
                playerChunkNum.clear();
                playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
                playerChunkNum.push_back(qCeil(qreal(m_player->rightX0() / m_map->chunkSize)));
            }
        } else if (playerChunkNum.size() == 0) {
            playerChunkNum.push_back(qCeil(qreal(m_player->leftX0() / m_map->chunkSize)));
            playerChunkNum.push_back(qCeil(qreal(m_player->rightX0() / m_map->chunkSize)));
        } else {
            qDebug() << "Something wrong, I can feel it";
        }
    }*/
}

void Scene::checkCollision(MoveDirection direction, float leftX, float rightX, float bottomY, float topY) {

    QString objectName = this->sender()->objectName();

    QVector<int> tempAllObjects; //номера всех объектов рядом и по пути от существа
    QVector<int> tempObjUnder; //временный вектор с номерами объектов под проверяемым существом
    QVector<int> tempObjOnLevel; //временный вектор с номерами объектов на уровне существа
    QVector<int> tempObjAbove; //временный вектор с номерами объектов выше проверяемого существа
    float distanceToNearestObj = 999.0f; //расстояние до ближайшего объекта
    int leftChunkNum = qCeil(qreal(leftX / m_map->chunkSize));
    int rightChunkNum = qCeil(qreal(rightX / m_map->chunkSize));
    int checkFromThisChunk = 0;
    int checkToThisChunk = 0;

    //здесь происходит проверка, не находится ли существо на краю карты
    if (leftChunkNum > 0 && rightChunkNum < m_map->countChunks) {
        checkFromThisChunk = leftChunkNum - 1;
        checkToThisChunk = rightChunkNum + 1;
    } else if (rightChunkNum == m_map->countChunks) {
        checkFromThisChunk = leftChunkNum - 1;
        checkToThisChunk = rightChunkNum;
    } else if (leftChunkNum == 0) {
        checkFromThisChunk = leftChunkNum;
        checkToThisChunk = rightChunkNum + 1;
    }

    //далее происходит запись всех объектов, которые находятся в проверяемых чанках
    for (int i = checkFromThisChunk; i <= checkToThisChunk; i++) {
        for (int j = 0; j < m_map->ChunkList[i].size(); j++) {
            if (!tempAllObjects.contains(m_map->ChunkList[i].at(j))) {
                tempAllObjects.push_back(m_map->ChunkList[i].at(j));
            }
        }
    }

    //разнесение объектов
    for (int i = 0; i < tempAllObjects.size(); i++) {
        if (m_map->ObjectData->at(ObjStartY).toFloat() + m_map->ObjectData->at(ObjSizeY).toFloat() <= bottomY) {
            tempObjUnder.push_back(tempAllObjects.at(i)); //запись объектов ниже ног существа
        } else if (m_map->ObjectData->at(ObjStartY).toFloat() < topY &&
                   m_map->ObjectData->at(ObjStartY).toFloat() + m_map->ObjectData->at(ObjSizeY).toFloat() > bottomY) {
            tempObjOnLevel.push_back(tempAllObjects.at(i)); //запись объектов на уровне существа
        } else if (m_map->ObjectData->at(ObjStartY).toFloat() > topY) {
            tempObjAbove.push_back(tempAllObjects.at(i)); //запись объектов выше головы существа
        }
    }

    switch(direction) {
    case MoveDirection::Left: {
        QVector<int> LeftObjects; //номера объектов, которые находятся левее существа
        for (int i = 0; i < tempObjOnLevel.size(); i++) {
            if (m_map->ObjectData[tempObjOnLevel.at(i)].at(ObjStartX).toFloat() +
                    m_map->ObjectData[tempObjOnLevel.at(i)].at(ObjSizeX).toFloat() <
                    leftX) {
                LeftObjects.push_back(tempObjOnLevel.at(i));
            }
        }
        for (int i = 0; i < LeftObjects.size(); i++) {
            if (leftX - (m_map->ObjectData[LeftObjects.at(i)].at(ObjStartX).toFloat() +
                         m_map->ObjectData[LeftObjects.at(i)].at(ObjSizeX).toFloat())
                    < distanceToNearestObj) {
                distanceToNearestObj = leftX - (m_map->ObjectData[LeftObjects.at(i)].at(ObjStartX).toFloat() +
                        m_map->ObjectData[LeftObjects.at(i)].at(ObjSizeX).toFloat());
            }
        }
        break;
    }
    case MoveDirection::Right: {
        QVector<int> RightObjects;
        for(int i = 0; i < tempObjOnLevel.size(); i++) {
            if (m_map->ObjectData[tempObjOnLevel.at(i)].at(ObjStartX).toFloat() > rightX) {
                RightObjects.push_back(tempObjOnLevel.at(i));
            }
        }
        for (int i = 0; i < RightObjects.size(); i++) {
            if (m_map->ObjectData[RightObjects.at(i)].at(ObjStartX).toFloat() - rightX < distanceToNearestObj) {
                distanceToNearestObj = m_map->ObjectData[RightObjects.at(i)].at(ObjStartX).toFloat() - rightX;
            }
        }
        break;
    }
    case MoveDirection::Up: {
        for (int i = 0; i < tempObjAbove.size(); i++) {
            if (m_map->ObjectData[tempObjAbove.at(i)].at(ObjStartY).toFloat() < distanceToNearestObj) {
                distanceToNearestObj = m_map->ObjectData[tempObjAbove.at(i)].at(ObjStartY).toFloat();
            }
        }
        break;
    }
    case MoveDirection::Down: {
        break;
    }
    }
    qDebug() << this->sender()->objectName();
    if (objectName.contains("Player")) {
        switch(direction) {
        case MoveDirection::Up: {
            if (distanceToNearestObj < m_player[objectName.split("Player").at(1).toInt()]->runSpeed.at(0)) {
                m_player[objectName.split("Player").at(1).toInt()]->runSpeed.replace(0, distanceToNearestObj);
            }
            break;
        }
        case MoveDirection::Down: {
            if (distanceToNearestObj < m_player[objectName.split("Player").at(1).toInt()]->runSpeed.at(1)) {
                m_player[objectName.split("Player").at(1).toInt()]->runSpeed.replace(1, distanceToNearestObj);
            }
            break;
        }
        case MoveDirection::Left: {
            if (distanceToNearestObj < m_player[objectName.split("Player").at(1).toInt()]->runSpeed.at(2)) {
                m_player[objectName.split("Player").at(1).toInt()]->runSpeed.replace(2, distanceToNearestObj);
            } else {
                m_player[objectName.split("Player").at(1).toInt()]->runSpeed.replace(2, 0.1f);
            }
            m_player[objectName.split("Player").at(1).toInt()]->setX0(m_player[objectName.split("Player").at(1).toInt()]->leftX0()
                    - m_player[objectName.split("Player").at(1).toInt()]->runSpeed.at(2));
            break;
        }
        case MoveDirection::Right: {
            if (distanceToNearestObj < m_player[objectName.split("Player").at(1).toInt()]->runSpeed.at(3)) {
                m_player[objectName.split("Player").at(1).toInt()]->runSpeed.replace(3, distanceToNearestObj);
            }
            break;
        }
        }
        //m_player[objectName.split("Player").at(1).toInt()]->runSpeed = speed;
    }
}

void Scene::checkPlayerCollision() {
    /*highestPointObj = 0.0f;
    QVector<int> tempObjUndPointsPlayer;
    objectsAbovePlayer.clear();
    if (playerChunkNum.size() == 1) {
        for (int i = 0; i < m_map->ChunkList[playerChunkNum.at(0)].size(); i++) {
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->leftX0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->leftX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->rightX0() && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->rightX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
        }
        //qDebug() << tempObjUndPointsPlayer;
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //удаление номеров объектов, которые выше ног игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > m_player->bottomY0() + 0.1f) {
                objectsAbovePlayer.push_back(tempObjUndPointsPlayer.at(i));
                tempObjUndPointsPlayer.remove(i);
            }
        }
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //поиск объекта, максимально близкого к ногам игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > highestPointObj) {
                highestPointObj = m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                        m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat();
            }
        }
    } else if (playerChunkNum.size() == 2) {
        for (int i = 0; i < m_map->ChunkList[playerChunkNum.at(0)].size(); i++) {
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->leftX0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() + m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->leftX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->rightX0() && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->rightX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
        }
        for (int i = 0; i < m_map->ChunkList[playerChunkNum.at(1)].size(); i++) {
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() < m_player->leftX0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(1).toFloat() > m_player->leftX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(1)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(1)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() < m_player->rightX0() && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(1).toFloat() > m_player->rightX0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(1)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(1)].at(i));
                }
            }
        }
        //qDebug() << tempObjUndPointsPlayer;
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //удаление номеров объектов, которые выше ног игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > m_player->bottomY0() + 0.1f) {
                objectsAbovePlayer.push_back(tempObjUndPointsPlayer.at(i));
                tempObjUndPointsPlayer.remove(i);
            }
        }
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //поиск объекта, максимально близкого к ногам игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > highestPointObj) {
                highestPointObj = m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                        m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat();
            }
        }
    }*/
}

void Scene::startGameSlot() {
    m_map = new map();
    for (int i = 0; i < m_map->numObjects; i++) {
        m_object[i] = new Object( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform, m_map->ObjectData[i], m_map->biome);
    }
    if (GameMode == GameModeState::Single) {
        m_player[0] = new Player( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform, m_map->PlayerCoords, 0 );
        connect(m_player[0], SIGNAL(jumpButtonPressed(float)), m_player[0], SLOT(playerJump(float)));
        connect(this, SIGNAL(changePlayerTexture()), m_player[0], SLOT(changePlayerTexture()));
        connect(m_player[0], SIGNAL(checkColl(MoveDirection, float, float, float, float)),
                this, SLOT(checkCollision(MoveDirection, float, float, float, float)));
    } else {

    }

    connect(doTick, SIGNAL(timeout()), SLOT(gameTick()));
    connect(this, SIGNAL(playerChangedChunkSignal()), SLOT(playerChangedChunk()));
    connect(this, SIGNAL(checkPlayerCollisionSignal()), SLOT(checkPlayerCollision()));

    emit playerChangedChunkSignal();
    emit checkPlayerCollisionSignal();

    doTick->start(tickTime);
}

void Scene::initializeGL() {

    glClearColor( 0.3294f, 0.6078f, 1.0f, 1.0f );

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    const char* vsrc =
            "attribute highp vec4 vertexAttr;"
            "uniform mediump mat4 matrix;"
            "attribute highp vec2 textureAttr;"
            "varying highp vec2 textureCoord;"
            "void main() {"
            "gl_Position = matrix * vertexAttr;"
            "textureCoord = textureAttr;}";
    vShader.compileSourceCode(vsrc);

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    const char* fsrc =
            "varying highp vec2 textureCoord;"
            "uniform sampler2D textureUniform;"
            "void main() {"
            "gl_FragColor = texture2D( textureUniform, textureCoord );}";
    fShader.compileSourceCode(fsrc);

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() ) {
        qWarning( "Error: unagle to link a shader program" );
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr" );
    m_textureAttr = m_program.attributeLocation( "textureAttr" );
    m_textureUniform = m_program.uniformLocation( "textureUniform" );
    m_matrixUniform = m_program.uniformLocation( "matrix" );

    connect(this, SIGNAL(startGame()), SLOT(startGameSlot()));
    emit startGame();
}

void Scene::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() ) {
        return;
    }

    QMatrix4x4 matrix;

    matrix.ortho( -0.0f, cameraSizeX, 0.0f, cameraSizeY, 10.0f, -10.0f);
    matrix.translate(matrixX, matrixY, matrixZ);
    m_program.setUniformValue( m_matrixUniform, matrix );

    for(int i = 0; i < m_map->numObjects; i++) {
        m_object[i]->draw();
    }

    if (GameMode == GameModeState::Single) {
        m_player[0]->draw();
    }

    m_program.release();
}

void Scene::resizeGL( int w, int h ) {
    glViewport( 0, 0, w, h );
}

void Scene::moveCamera() {
    /*if (stickCameraToThePlayer) {
        if (m_player->bottomY0() >= 25.0f) {
            matrixY = -m_player->bottomY0() + 25;
        } else {
            matrixY = 0.0f;
        }
        if (m_player->leftX0() >= cameraSizeX / 2 + cameraSizeX / 4 - matrixX) {
            matrixX -= step;
        } else if (m_player->leftX0() <= cameraSizeX / 2 - cameraSizeX / 4 - matrixX) {
            matrixX += step;
        }
    }*/
}

void Scene::keyPressEvent( QKeyEvent *event ) {
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
            //m_player->setY0( m_player->bottomY0() - step);
            break;
        case Qt::Key_Left:
            pressedKeys.push_back(Qt::Key_Left);
            //m_player->setX0( m_player->leftX0() - step);
            break;
        case Qt::Key_Right:
            pressedKeys.push_back(Qt::Key_Right);
            //m_player->setX0( m_player->leftX0() + step);
            break;
        case Qt::Key_Up:
            pressedKeys.push_back(Qt::Key_Up);
            //m_player->setY0( m_player->bottomY0() + step);
            break;
        case Qt::Key_Space:
            pressedKeys.push_back(Qt::Key_Space);
            //emit m_player->jumpButtonPressed();
            break;
        default:
            qDebug() << event->key();
            break;
        }
        //qDebug() << pressedKeys;
    }
}

void Scene::keyReleaseEvent( QKeyEvent *event ) {
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
        case Qt::Key_Space:
            //m_player->isPlayerJump = false;
            if (pressedKeys.size() == 1) {
                pressedKeys.remove(0);
            } else {
                for (int i = 0; i < pressedKeys.size(); i++) {
                    if (pressedKeys.at(i) == Qt::Key_Space) {
                        pressedKeys.remove(i);
                    }
                }
            }
            break;
        default:
            qDebug() << event->key();
            break;
        }
        //qDebug() << pressedKeys;
    }
}
