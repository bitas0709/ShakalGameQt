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

    int currentMap = 1; //задание номера карты

    QList<QString> ObjectData[10]; //данные об объектах, считанных из файла
    int numObjects; //количество объектов, считанных из файла

    void sortObjects(); //сортировка объектов и разнесение их по чанкам

    QVector<int> ChunkList[100]; //вектор для хранения номеров объектов в чанках
    float minX = 0.0f, maxX = 0.0f; //крайняя левая координата X и крайняя правая
    float mapSize; //размер карты
    int countChunks; //количество чанков
    float chunkSize = 5.0f; //размер шага для разделения карты на чанки по оси X

private:

    void readDataFromFile( int number ); //считывание данных из файла
    bool readingObjectData = false;

    int realNumOfObjects = 0;

};

#endif // MAP_H
