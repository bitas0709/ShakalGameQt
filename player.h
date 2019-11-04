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

    void draw(); //отрисовка игрока

    void setX0( float x ); //задание новой координаты X
    void setY0( float y ); //задание новой координаты Y

    float x0() const; //получение текущей координаты X
    float y0() const; //получение текущей координаты Y

    float leftX0() const; //получение текущей координаты X левой стороны
    float rightX0() const; //получение текущей координаты X правой стороны

    float bottomY0() const; //получение текущей координаты Y ног
    float topY0() const; //получение текущей координаты Y головы

    float startX = 15.0f;
    float startY = 10.0f;
    float sizeX = 2.0f;
    float sizeY = 3.0f;

    enum EnumLineOfSightPlayer { //направление взгляда игрока
        LookLeft, LookRight
    };
    int CurrentLineOfSightPlayer = LookRight;

    float playerJumpHeight = 8.0f;
    float playerCoordBeforeJump;
    bool isPlayerJump = false;

    float maxRunSpeed = 0.5f; //максимальная скорость бега
    float runCoefficient = 0.125f;

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

    float CenterCoordX = (startX + sizeX) / 2.0f;
    float CenterCoordY = (startY + sizeY) / 2.0f;
};

#endif // TRIANGLE_H
