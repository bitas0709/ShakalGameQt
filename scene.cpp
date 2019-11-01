#include "scene.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent )
{
    this->setFocusPolicy( Qt::StrongFocus );
    doTick = new QTimer();
}

Scene::~Scene()
{
    makeCurrent();
    delete m_player;
    for (int i = 0; i < m_map->numObjects; i++) {
        delete m_object[i];
    }
    doneCurrent();
}

void Scene::gameTick() {
    if (qCeil(qreal(m_player->x0() / m_map->chunkSize)) == qCeil(qreal((m_player->x0() + m_player->sizeX) / m_map->chunkSize))) {
        if (playerChunkNum.size() == 1) {
            if (playerChunkNum.at(0) != qCeil(qreal(m_player->x0() / m_map->chunkSize))) {
                playerChunkNum.remove(0);
                playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
            }
        } else if (playerChunkNum.size() == 2) {
            playerChunkNum.clear();
            playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
        } else if (playerChunkNum.size() == 0) {
            playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
        } else {
            qDebug() << "Something wrong, I can feel it";
        }
    } else {
        if (playerChunkNum.size() == 1) {
            playerChunkNum.clear();
            playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
            playerChunkNum.push_back(qCeil(qreal((m_player->x0() + m_player->sizeX) / m_map->chunkSize)));
        } else if (playerChunkNum.size() == 2) {
            if (playerChunkNum.at(0) != qCeil(qreal(m_player->x0() / m_map->chunkSize)) &&
                    playerChunkNum.at(1) != qCeil(qreal((m_player->x0() + m_player->sizeX) / m_map->chunkSize))) {
                playerChunkNum.clear();
                playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
                playerChunkNum.push_back(qCeil(qreal((m_player->x0() + m_player->sizeX) / m_map->chunkSize)));
            }
        } else if (playerChunkNum.size() == 0) {
            playerChunkNum.push_back(qCeil(qreal(m_player->x0() / m_map->chunkSize)));
            playerChunkNum.push_back(qCeil(qreal((m_player->x0() + m_player->sizeX) / m_map->chunkSize)));
        } else {
            qDebug() << "Something wrong, I can feel it";
        }
    }
    //qDebug() << "playerChunkNum =" << playerChunkNum;
    float highestPointObj = 0.0f;
    QVector<int> tempObjUndPointsPlayer;
    if (playerChunkNum.size() == 1) {
        for (int i = 0; i < m_map->ChunkList[playerChunkNum.at(0)].size(); i++) {
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->x0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->x0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->x0() + m_player->sizeX && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->x0() + m_player->sizeX) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
        }
        qDebug() << tempObjUndPointsPlayer;
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //удаление номеров объектов, которые выше ног игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > m_player->y0()) {
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
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->x0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() + m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->x0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() < m_player->x0() + m_player->sizeX && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(0)].at(i)].at(1).toFloat() > m_player->x0() + m_player->sizeX) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(0)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(0)].at(i));
                }
            }
        }
        for (int i = 0; i < m_map->ChunkList[playerChunkNum.at(1)].size(); i++) {
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() < m_player->x0() && //поиск объектов под левой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(1).toFloat() > m_player->x0()) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(1)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(1)].at(i));
                }
            }
            if (m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() < m_player->x0() + m_player->sizeX && //поиск объектов под правой точкой игрока
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(3).toFloat() +
                    m_map->ObjectData[m_map->ChunkList[playerChunkNum.at(1)].at(i)].at(1).toFloat() > m_player->x0() + m_player->sizeX) {
                if (!tempObjUndPointsPlayer.contains(m_map->ChunkList[playerChunkNum.at(1)].at(i))) {
                    tempObjUndPointsPlayer.push_back(m_map->ChunkList[playerChunkNum.at(1)].at(i));
                }
            }
        }
        qDebug() << tempObjUndPointsPlayer;
        for (int i = 0; i < tempObjUndPointsPlayer.size(); i++) { //удаление номеров объектов, которые выше ног игрока
            if (m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(4).toFloat() +
                    m_map->ObjectData[tempObjUndPointsPlayer.at(i)].at(2).toFloat() > m_player->y0()) {
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
    }
    qDebug() << "highestPointObj =" << highestPointObj;
    if (!m_player->isPlayerJump) {
        if (m_player->y0() - 0.1f > highestPointObj) {
            m_player->isPlayerOnGround = false;
        } else {
            m_player->isPlayerOnGround = true;
        }
    }
    if (!m_player->isPlayerOnGround) {
        //emit m_player->jumpButtonPressed(step);
        if (!m_player->isPlayerJump) {
            if (m_player->y0() > 0) {
                m_player->setY0(m_player->y0() - step);
            }
        }
    }
    if (pressedKeys.size() != 0) {
        for (int i = 0; i < pressedKeys.size(); i++) {
            if (pressedKeys[i] == Qt::Key_Left) {
                QVector<int> numObjects; //номера объектов в двух чанках
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
                qDebug() << "numObjects =" << numObjects;
                bool playerCanRun = true;
                for (int i = 0; i < numObjects.size(); i++) {
                    if (qFuzzyCompare(m_player->x0(), m_map->ObjectData[numObjects.at(i)].at(3).toFloat()
                                      + m_map->ObjectData[numObjects.at(i)].at(1).toFloat())) {
                        if (m_player->y0() + m_player->sizeY >= m_map->ObjectData[numObjects.at(i)].at(4).toFloat() &&
                                m_player->y0() < m_map->ObjectData[numObjects.at(i)].at(4).toFloat() +
                                m_map->ObjectData[numObjects.at(i)].at(2).toFloat()) {
                            //если голова выше нижней точки объекта и ноги ниже верхней точки объекта
                            playerCanRun = false;
                        }
                    }
                }
                if (playerCanRun) {
                    if (m_player->x0() > m_map->minX) {
                        m_player->setX0( m_player->x0() - step);
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
                qDebug() << "numObjects =" << numObjects;
                bool playerCanRun = true;
                for (int i = 0; i < numObjects.size(); i++) {
                    if (qFuzzyCompare(m_player->x0() + m_player->sizeX, m_map->ObjectData[numObjects.at(i)].at(3).toFloat())) {
                        if (m_player->y0() + m_player->sizeY >= m_map->ObjectData[numObjects.at(i)].at(4).toFloat() &&
                                m_player->y0() < m_map->ObjectData[numObjects.at(i)].at(4).toFloat() +
                                m_map->ObjectData[numObjects.at(i)].at(2).toFloat()) {
                            //если голова выше нижней точки объекта и ноги ниже верхней точки объекта
                            playerCanRun = false;
                        }
                    }
                }
                if (playerCanRun) {
                    if (m_player->x0() + m_player->sizeX < m_map->maxX) {
                        m_player->setX0( m_player->x0() + step);
                    }
                }
                //m_player->setX0( m_player->x0() + step );
                if (stickCameraToThePlayer) {
                    moveCamera();
                }
                if (m_player->CurrentLineOfSightPlayer == m_player->LookLeft) {
                    m_player->CurrentLineOfSightPlayer = m_player->LookRight;
                    emit changePlayerTexture();
                }
            } else if (pressedKeys[i] == Qt::Key_Space) {
                if (m_player->isPlayerOnGround) {
                    //m_player->setY0(m_player->y0() + step);
                    m_player->isPlayerJump = true;
                    emit m_player->jumpButtonPressed(step);
                }
            } else if (pressedKeys[i] == Qt::Key_Down) {
                m_player->setY0(m_player->y0() - step);
                moveCamera();
            } else if (pressedKeys[i] == Qt::Key_Up) {
                m_player->setY0(m_player->y0() + step);
                moveCamera();
            }
        }
    }
    //qDebug() << "NumObject =" << CurrentObjNumPlayer.at(0);
    update();
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

    m_player = new Player( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    connect(m_player, SIGNAL(jumpButtonPressed(float)), m_player, SLOT(playerJump(float)));
    m_map = new map();
    for (int i = 0; i < m_map->numObjects; i++) {
        m_object[i] = new Object( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform, m_map->ObjectData[i]);
    }

    connect(doTick, SIGNAL(timeout()), SLOT(gameTick()));
    connect(this, SIGNAL(changePlayerTexture()), m_player, SLOT(changePlayerTexture()));
    doTick->start(tickTime);
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

    m_player->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h ) {
    glViewport( 0, 0, w, h );
}

void Scene::moveCamera() {
    if (stickCameraToThePlayer) {
        if (m_player->y0() >= 25.0f) {
            matrixY = -m_player->y0() + 25;
        } else {
            matrixY = 0.0f;
        }
        if (m_player->x0() >= cameraSizeX / 2 + cameraSizeX / 4 - matrixX) {
            matrixX -= step;
        } else if (m_player->x0() <= cameraSizeX / 2 - cameraSizeX / 4 - matrixX) {
            matrixX += step;
        }
    }
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
        case Qt::Key_Space:
            pressedKeys.push_back(Qt::Key_Space);
            //emit m_player->jumpButtonPressed();
            break;
        default:
            qDebug() << event->key();
            break;
        }
        qDebug() << pressedKeys;
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
            m_player->isPlayerJump = false;
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
        qDebug() << pressedKeys;
    }
}
