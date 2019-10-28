#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QList>
#include <QtMath>
#include "objects.h"

class map
{
public:
    map();
    ~map();

    void draw();

    int currentMap = 1;

    QList<QString> ObjectData[10];
    int numObjects;

    void sortObjects();

    QVector<int> ChunkList[100];
    float mapSize; //размер карты
    int countChunks; //количество чанков
    float chunkSize = 5.0f; //размер шага для разделения карты на чанки по оси X

private:

    void readDataFromFile( int number );
    bool readingObjectData = false;

    int realNumOfObjects = 0;

};

#endif // MAP_H
