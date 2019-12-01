#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy( QOpenGLShaderProgram *program,
           int vertexAttr, int textureAttr, int textureUniform, QVector<float> EnemyCoords, int EnemyNumber );

    void draw();

    float leftX0() const;
    float rightX0() const;
    float bottomY0() const;
    float topY0() const;

    void setX0( float x );
    void setY0( float y );

    bool gotCoords = false;
    float startX = 20.0f;
    float startY = 20.0f;

    float sizeX = 10.0f;
    float sizeY = 10.0f;

private:

    void initVertices();
    void initTextureCoord();

    std::vector<float> m_vertices;
    std::vector<float> m_textureCoords;

    QOpenGLShaderProgram *m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;

    QOpenGLTexture *m_texture;

};

#endif // ENEMY_H
