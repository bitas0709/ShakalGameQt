#include "objects.h"

Object::Object( QOpenGLShaderProgram *program,
                int vertexAttr, int textureAttr, int textureUniform, QList<QString> ObjectData ):
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_textureAttr( textureAttr ),
    m_textureUniform( textureUniform )
{
    initVertices( ObjectData );
    initTextureCoords();

    if (ObjectData.at(7).contains("stone")) {
        m_texture = new QOpenGLTexture( QImage(":/Textures/Stone.png") );
    } else if (ObjectData.at(7).contains("grass")) {
        m_texture = new QOpenGLTexture( QImage(":/Textures/Grass.jpg") );
    } else if (ObjectData.at(7).contains("block")) {
        m_texture = new QOpenGLTexture( QImage(":/Textures/Blocks.jpg") );
    }
}

Object::~Object() {

}

void Object::initVertices( QList<QString> ObjectData ) {
    m_vertices.resize( 18 );

    //0
    m_vertices[0] = ObjectData.at(3).toFloat();
    m_vertices[1] = ObjectData.at(4).toFloat();
    m_vertices[2] = 0.0f;

    //1
    m_vertices[3] = ObjectData.at(3).toFloat() + ObjectData.at(1).toFloat();
    m_vertices[4] = ObjectData.at(4).toFloat();
    m_vertices[5] = 0.0f;

    //2
    m_vertices[6] = ObjectData.at(3).toFloat();
    m_vertices[7] = ObjectData.at(4).toFloat() + ObjectData.at(2).toFloat();
    m_vertices[8] = 0.0f;

    //3
    m_vertices[9] = ObjectData.at(3).toFloat();
    m_vertices[10] = ObjectData.at(4).toFloat() + ObjectData.at(2).toFloat();
    m_vertices[11] = 0.0f;

    //4
    m_vertices[12] = ObjectData.at(3).toFloat() + ObjectData.at(1).toFloat();
    m_vertices[13] = ObjectData.at(4).toFloat();
    m_vertices[14] = ObjectData.at(5).toFloat();

    //5
    m_vertices[15] = ObjectData.at(3).toFloat() + ObjectData.at(1).toFloat();
    m_vertices[16] = ObjectData.at(4).toFloat() + ObjectData.at(2).toFloat();
    m_vertices[17] = 0.0f;
}

void Object::initTextureCoords() {
    m_textureCoords.resize( 12 );

    //0
    m_textureCoords[0] = 0.0f;
    m_textureCoords[1] = 0.0f;

    // 1
    m_textureCoords[2] = 1.0f;
    m_textureCoords[3] = 0.0f;

    // 2
    m_textureCoords[4] = 0.0f;
    m_textureCoords[5] = 1.0f;

    // 3
    m_textureCoords[6] = 0.0f;
    m_textureCoords[7] = 1.0f;

    // 4
    m_textureCoords[8] = 1.0f;
    m_textureCoords[9] = 0.0f;

    // 5
    m_textureCoords[10] = 1.0f;
    m_textureCoords[11] = 1.0f;
}

void Object::draw() {
    m_texture->bind();
    m_program->setAttributeArray( m_vertexAttr, m_vertices.data(), 3 );
    m_program->setAttributeArray( m_textureAttr, m_textureCoords.data(), 2 );
    m_program->setUniformValue( m_textureUniform, 0 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_textureAttr );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_textureAttr );
}
