#include "scene.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent )
{
    this->setFocusPolicy( Qt::StrongFocus );
    doTick = new QTimer();
    connect(doTick, SIGNAL(timeout()), this, SLOT(tick()));
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


void Scene::initializeGL() {

    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

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
    m_map = new map();

    for (int i = 0; i < m_map->numObjects; i++) {
        m_object[i] = new Object( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform, m_map->ObjectData[i]);
    }
}

void Scene::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() ) {
        return;
    }

    QMatrix4x4 matrix;

    //matrix.ortho( -2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f );
    matrix.ortho( -10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
    matrix.translate(matrixX, matrixY, matrixZ);
    //matrix.translate( 0.0f, 0.0f, -1.0f );
    m_program.setUniformValue( m_matrixUniform, matrix );

    //m_map->draw();

    for(int i = 0; i < m_map->numObjects; i++) {
        m_object[i]->draw();
    }

    m_player->draw();

    m_program.release();
}

void Scene::tick() {
    if(!pressedKeys.isEmpty()) {
        for (int i = 0; i < pressedKeys.size(); i++) {
            if (pressedKeys.at(i) == Qt::Key_A || pressedKeys.at(i) == Qt::Key_D ||
                    pressedKeys.at(i) == Qt::Key_S || pressedKeys.at(i) == Qt::Key_W) {
                m_player->movePlayertimer().start(m_player->timerTimeout);
            }
        }
    }
}

void Scene::resizeGL( int w, int h ) {
    glViewport( 0, 0, w, h );
}

void Scene::keyPressEvent(QKeyEvent *event) {
    //const float step = 0.1f;

    if(!event->isAutoRepeat()) {
        switch(event->key()) {
        case Qt::Key_A:
            pressedKeys.push_back(Qt::Key_A);
            matrixX-=0.1f;
            break;
        case Qt::Key_D:
            pressedKeys.push_back(Qt::Key_D);
            matrixZ-=0.1f;
            break;
        case Qt::Key_E:
            pressedKeys.push_back(Qt::Key_E);
            matrixZ+=0.1f;
            break;
        case Qt::Key_Q:
            pressedKeys.push_back(Qt::Key_Q);
            matrixX+=0.1f;
            break;
        case Qt::Key_R:
            pressedKeys.push_back(Qt::Key_R);
            matrixX = 0.0f;
            matrixY = 0.0f;
            matrixZ = -1.0f;
            break;
        case Qt::Key_S:
            pressedKeys.push_back(Qt::Key_S);
            matrixY-=0.1f;
            break;
        case Qt::Key_W:
            pressedKeys.push_back(Qt::Key_W);
            matrixY+= 0.1f;
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
    update();
}

void Scene::keyReleaseEvent(QKeyEvent *event) {
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
