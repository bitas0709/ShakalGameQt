#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>

class Player : public QObject
{
    Q_OBJECT
public:
    Player( QOpenGLShaderProgram *program,
              int vertexAttr, int textureAttr, int textureUniform );
    ~Player();

    void draw();

    void setX0( float x );
    void setY0( float y );

    float x0() const;
    float y0() const;

    enum EnumLineOfSightPlayer { //направление взгляда игрока
        LookLeft, LookRight
    };
    int CurrentLineOfSightPlayer = LookRight;

    float playerJumpHeight = 15.0f;
    float playerCoordBeforeJump;
    bool isPlayerJump = false;

    float maxRunSpeed = 3.0f; //максимальная скорость бега
    float timeOfIncreasingSpeed = 0.5f; //в секундах
    float RunSpeedIncreaseCoefficient = 0.5f; //не может быть больше максимальной скорости бега игрока
    float currentPlayerXSpeed = 0.0f; //скорость игрока по оси X
    float currentPlayerYSpeed = 0.0f; //скорость игрока по оси y
    float playerWeight = 60.0f; //"вес" игрока

    bool isPlayerOnGround = true;

signals:

    void jumpButtonPressed(float);

private slots:

    void playerJump(float step);
    void changePlayerTexture();

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

    //float CoordX;
    //float CoordY;

    //float m_x0;
    //float m_y0;
    //float m_size;

    float startX = 15.0f;
    float startY = 10.0f;
    float sizeX = 2.0f;
    float sizeY = 3.0f;
    float CenterCoordX = (startX + sizeX) / 2.0f;
    float CenterCoordY = (startY + sizeY) / 2.0f;
};

#endif // TRIANGLE_H
