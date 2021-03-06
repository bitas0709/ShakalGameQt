#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QList>
#include <QtMath>
#include <QPainter>

class Object {
public:
    Object( QOpenGLShaderProgram *program,
            int vertexAttr, int textureAttr, int textureUniform, QList<QString> ObjectData, QString biome, int numObject );
    //Object();
    ~Object();

    void draw(); //отрисовка объекта

private:

    void initVertices( QList<QString> ObjectData ); //задание координат объектов
    void initTextureCoords(); //задание координат текстур объектов

    std::vector<float> m_vertices; //вектор координат вершин объектов
    std::vector<float> m_textureCoords; //вектор координат вершин текстур объектов

    QOpenGLShaderProgram *m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;

    QOpenGLTexture *m_texture;

    int startCropX = 0, startCropY = 0;

};

#endif // OBJECTS_H
