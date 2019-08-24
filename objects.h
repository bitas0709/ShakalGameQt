#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QList>

class Object {
public:
    Object( QOpenGLShaderProgram *program,
            int vertexAttr, int textureAttr, int textureUniform, QList<QString> ObjectData );
    ~Object();

    void draw();

private:

    void initVertices( QList<QString> ObjectData );
    void initTextureCoords();

    std::vector<float> m_vertices;
    std::vector<float> m_textureCoords;

    QOpenGLShaderProgram *m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;

    QOpenGLTexture *m_texture;
};

#endif // OBJECTS_H
