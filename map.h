#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QList>
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

private:

    void readDataFromFile( int number );
    bool readingObjectData = false;

    int realNumOfObjects = 0;

};

#endif // MAP_H
