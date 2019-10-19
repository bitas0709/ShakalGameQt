#include "player.h"

Player::Player( QOpenGLShaderProgram *program,
                    int vertexAttr, int textureAttr, int textureUniform ) :
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_textureAttr( textureAttr ),
    m_textureUniform( textureUniform )
{
    initVertices();
    initTextureCoord();

    if (CurrentLineOfSightPlayer == EnumLineOfSightPlayer::LookLeft) {
        m_texture = new QOpenGLTexture( QImage( ":/Textures/Mario.png" ).mirrored(true, false) );
    } else {
        m_texture = new QOpenGLTexture( QImage( ":/Textures/Mario.png" ) );
    }

}

Player::~Player() {
    delete m_texture;
}

void Player::changePlayerTexture() {
    if (CurrentLineOfSightPlayer == EnumLineOfSightPlayer::LookRight) {
        m_texture = new QOpenGLTexture(QImage( ":/Textures/Mario.png" ));
    } else {
        m_texture = new QOpenGLTexture(QImage( ":/Textures/Mario.png" ).mirrored(true, false));
    }
}

void Player::playerJump() {

}

void Player::draw()
{
    m_texture->bind();
    m_program->setAttributeArray( m_vertexAttr, m_vertices.data(), 3 );
    m_program->setAttributeArray( m_textureAttr, m_textureCoords.data(), 2 );
    m_program->setUniformValue( m_textureUniform, 0 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_textureAttr );

    glDrawArrays( GL_TRIANGLES, 0, static_cast<uint>(m_vertices.size()) / 3 );

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_textureAttr );
}

void Player::initVertices() {
    m_vertices.resize( 18 );

    //0
    m_vertices[0] = startX;
    m_vertices[1] = startY;
    m_vertices[2] = 0.0f;

    //1
    m_vertices[3] = startX + sizeX;
    m_vertices[4] = startY;
    m_vertices[5] = 0.0f;

    //2
    m_vertices[6] = startX;
    m_vertices[7] = startY + sizeY;
    m_vertices[8] = 0.0f;

    //3
    m_vertices[9] = startX;
    m_vertices[10] = startY + sizeY;
    m_vertices[11] = 0.0f;

    //4
    m_vertices[12] = startX + sizeX;
    m_vertices[13] = startY;
    m_vertices[14] = 0.0f;

    //5
    m_vertices[15] = startX + sizeX;
    m_vertices[16] = startY + sizeY;
    m_vertices[17] = 0.0f;

}

void Player::initTextureCoord() {
    m_textureCoords.resize( 12 );

    //0
    m_textureCoords[0] = 0.0f;
    m_textureCoords[1] = 1.0f;

    // 1
    m_textureCoords[2] = 1.0f;
    m_textureCoords[3] = 1.0f;

    // 2
    m_textureCoords[4] = 0.0f;
    m_textureCoords[5] = 0.0f;

    // 3
    m_textureCoords[6] = 0.0f;
    m_textureCoords[7] = 0.0f;

    // 4
    m_textureCoords[8] = 1.0f;
    m_textureCoords[9] = 1.0f;

    // 5
    m_textureCoords[10] = 1.0f;
    m_textureCoords[11] = 0.0f;
}

void Player::setX0( float x ) {
    qDebug() << "setX0 = " << x;
    startX = x;
    initVertices();
}

void Player::setY0( float y ) {
    qDebug() << "setY0 = " << y;
    startY = y;
    initVertices();
}

float Player::x0() const {
    return startX;
}

float Player::y0() const {
    return startY;
}
