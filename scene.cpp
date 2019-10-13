#include "scene.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent )
{
    this->setFocusPolicy( Qt::StrongFocus );
    gm = new GameEngine();
    connect(this, SIGNAL(keyPressGot( QKeyEvent* )), gm, SLOT(keyPressTaken( QKeyEvent* )));
    connect(this, SIGNAL(keyReleaseGot( QKeyEvent* )), gm, (SLOT(keyReleaseTaken( QKeyEvent* ))));
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

    //doTick = new QTimer();
    //connect(doTick, SIGNAL(timeout()), SLOT(gameTick()));
    //doTick->start(tickTime);
}

void Scene::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() ) {
        return;
    }

    QMatrix4x4 matrix;

    matrix.ortho( -10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
    matrix.translate(matrixX, matrixY, matrixZ);
    m_program.setUniformValue( m_matrixUniform, matrix );

    //m_map->draw();

    for(int i = 0; i < m_map->numObjects; i++) {
        m_object[i]->draw();
    }

    m_player->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h ) {
    glViewport( 0, 0, w, h );
}

void Scene::keyPressEvent( QKeyEvent *event ) {
    emit keyPressGot( event );
}

void Scene::keyReleaseEvent( QKeyEvent *event ) {
    emit keyReleaseGot( event );
}
