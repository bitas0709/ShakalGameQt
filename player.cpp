#include "player.h"

Player::Player( QOpenGLShaderProgram *program,
                    int vertexAttr, int textureAttr, int textureUniform ) :
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_textureAttr( textureAttr ),
    m_textureUniform( textureUniform ),
    m_x0( -0.5f ),
    m_y0( -0.5f ),
    m_size( 1.0f )
{
    initVertices();
    initTextureCoord();

    m_texture = new QOpenGLTexture( QImage( ":/Textures/Ricardo.jpg") );
}

Player::~Player() {
    delete m_texture;
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
    m_vertices.resize( 9 );

    // 0 BOTTOM LEFT
    m_vertices[0] = m_x0;
    m_vertices[1] = m_y0;
    m_vertices[2] = 0.0f;

    // 1 BOTTOM RIGHT
    m_vertices[3] = m_x0 + m_size;
    m_vertices[4] = m_y0;
    m_vertices[5] = 0.0f;

    // 2 TOP
    m_vertices[6] = m_x0 + m_size / 2.0f;
    m_vertices[7] = m_y0 + m_size;
    m_vertices[8] = 0.0f;
}

void Player::initTextureCoord() {
    m_textureCoords.resize( 6 );

    // 0
    m_textureCoords[0] = 0.0f;
    m_textureCoords[1] = 1.0f;

    //1
    m_textureCoords[2] = 1.0f;
    m_textureCoords[3] = 1.0f;

    //2
    m_textureCoords[4] = 0.5f;
    m_textureCoords[5] = 0.0f;
}

void Player::setX0( float x ) {
    m_x0 = x;
    initVertices();
}

void Player::setY0( float y ) {
    m_y0 = y;
    initVertices();
}

float Player::x0() const {
    return m_x0;
}

float Player::y0() const {
    return m_y0;
}
