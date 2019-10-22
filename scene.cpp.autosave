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
    if (pressedKeys.size() != 0) {
        //const float step = 0.1f;
        for (int i = 0; i < pressedKeys.size(); i++) {
            if (pressedKeys[i] == Qt::Key_Left) {
                m_player->setX0( m_player->x0() - step );
                moveCamera();
                if (m_player->CurrentLineOfSightPlayer == m_player->LookRight) {
                    m_player->CurrentLineOfSightPlayer = m_player->LookLeft;
                    emit changePlayerTexture();
                }
            } else if (pressedKeys[i] == Qt::Key_Right) {
                m_player->setX0( m_player->x0() + step );
                moveCamera();
                if (m_player->CurrentLineOfSightPlayer == m_player->LookLeft) {
                    m_player->CurrentLineOfSightPlayer = m_player->LookRight;
                    emit changePlayerTexture();
                }
            } else if (pressedKeys[i] == Qt::Key_Space) {
                if (!m_player->isPlayerOnGround) {
                    emit m_player->jumpButtonPressed();
                }
            }
        }
    }
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
    connect(m_player, SIGNAL(jumpButtonPressed()), m_player, SLOT(playerJump()));
    m_map = new map();
    for (int i = 0; i < m_map->numObjects; i++) {
        m_object[i] = new Object( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform, m_map->ObjectData[i]);
        if (m_map->ObjectData[i].at(6).contains("no")) { //внесение в список объектов, через которые игрок не должен проходить
            collisionList.insert(i, m_map->ObjectData[i].at(3).toFloat()); //внесение начальной координаты x
            collisionList.insert(i, m_map->ObjectData[i].at(1).toFloat() + m_map->ObjectData[i].at(3).toFloat()); //координата x конца объекта
            collisionList.insert(i, m_map->ObjectData[i].at(4).toFloat()); //внесение начальной координаты y
            collisionList.insert(i, m_map->ObjectData[i].at(2).toFloat() + m_map->ObjectData[i].at(4).toFloat()); //координата y конца объекта
        }
    }
    qDebug() << "collisionList size =" << collisionList.size();
    qDebug() << "collisionList unique keys =" << collisionList.uniqueKeys().size();
    qDebug() << "collisionList before sorting" << collisionList;

    bool allCollisionListObjectsSorted = false;
    while (!allCollisionListObjectsSorted) {
        allCollisionListObjectsSorted = true;
        for (int i = 2; i <= collisionList.uniqueKeys().size(); i++) {
            if (collisionList.value(i) < collisionList.value(i - 1)) {
                allCollisionListObjectsSorted = false;
                QList<float> tempSortList = collisionList.values(i - 1);
                QList<float> tempSortList2 = collisionList.values(i);
                collisionList.remove(i - 1);
                for (int j = tempSortList2.size() - 1; j >= 0; j--) {
                    collisionList.insert(i - 1, tempSortList2.at(j));
                }
                collisionList.remove(i);
                for (int j = tempSortList.size() - 1; j >= 0; j--) {
                    collisionList.insert(i, tempSortList.at(j));
                }
            }
        }
    }

    qDebug() << "collisionList after sorting" << collisionList;

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

    m_map->draw();

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
            matrixY = m_player->y0();
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
            emit m_player->jumpButtonPressed();
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
