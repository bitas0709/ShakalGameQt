#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>

class Player
{
public:
    Player( QOpenGLShaderProgram *program,
              int vertexAttr, int textureAttr, int textureUniform );
    ~Player();

    void draw();

    void setX0( float x );
    void setY0(float y );

    float x0() const;
    float y0() const;

    float maxRunSpeed = 3.0f; //максимальная скорость бега
    float timeOfIncreasingSpeed = 0.5f; //в секундах
    float RunSpeedIncreaseCoefficient = 0.5f; //не может быть больше максимальной скорости бега игрока
    float currentPlayerXSpeed = 0.0f; //скорость игрока по оси X
    float currentPlayerYSpeed = 0.0f; //скорость игрока по оси y
    float playerWeight = 60.0f; //"вес" игрока

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

    float m_x0;
    float m_y0;
    float m_size;
};

#endif // TRIANGLE_H
