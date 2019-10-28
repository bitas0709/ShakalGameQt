#include "map.h"

map::map()
{

    readDataFromFile( currentMap );

}

map::~map() {
}

void map::draw() {

}

void map::readDataFromFile( int number ) {

    QString fileName;
    fileName = ":/Maps/Map00";
    fileName.append(QString::number(number));
    fileName.append("/objects.dat");
    qDebug() << fileName;

    QFile map(fileName);

    if (!map.open(QIODevice::ReadOnly)) {
        qWarning("Error while open file!");
    }

    int numObject = 0;

    while(!map.atEnd()) {
        QString buff = map.readLine();
        if(buff.contains("//")) {
            if(buff.split("//").at(0) == "") {
                qDebug() << "Пропуск комментария";
                //Пропуск строки, так как она является комментарием
            }
        } else {
            if (!readingObjectData) {
                if (buff.contains("Objects")) {
                    numObjects = buff.split("Objects: ").at(1).toInt();
                    qDebug() << "numObjects =" << numObjects;
                } else if (buff.contains("Object_")) {
                    realNumOfObjects++;
                    qDebug() << "object" << buff.split("Object_").at(1).toInt();
                    readingObjectData = true;
                }
            } else {
                if (!buff.contains("}")) {
                    if (buff.contains("id:")) {
                        numObject = buff.split("id:").at(1).toInt();
                    } else if (buff.contains("type:")) {
                        ObjectData[numObject].push_back(buff.split("type:").at(1)); //0
                    } else if (buff.contains("sizeX:")) {
                        ObjectData[numObject].push_back(buff.split("sizeX:").at(1)); //1
                    } else if (buff.contains("sizeY:")) {
                        ObjectData[numObject].push_back(buff.split("sizeY:").at(1)); //2
                    } else if (buff.contains("startX:")) {
                        ObjectData[numObject].push_back(buff.split("startX:").at(1)); //3
                    } else if (buff.contains("startY:")) {
                        ObjectData[numObject].push_back(buff.split("startY:").at(1)); //4
                    } else if (buff.contains("coordZ")) {
                        ObjectData[numObject].push_back(buff.split("coordZ:").at(1)); //5
                    } else if (buff.contains("passable:")) {
                        ObjectData[numObject].push_back(buff.split("passable:").at(1)); //6
                    } else if (buff.contains("texture:")) {
                        ObjectData[numObject].push_back(buff.split("texture:").at(1)); //7
                    }
                } else {
                    readingObjectData = false;
                    numObject++;
                }
            }
        }
    }
    sortObjects();
    for (int i = 0; i < numObjects; i++) {
        qDebug() << ObjectData[i];
    }
    map.close();

}

void map::sortObjects() {
    float minX = 0.0f, maxX = 0.0f;
    //int countChunks; //количество чанков
    bool allObjectsSorted = false;
    QList<QString> tempObjectData;
    while (!allObjectsSorted) {
        allObjectsSorted = true;
        for (int i = 1; i < numObjects; i++) {
            if (ObjectData[i].at(5) < ObjectData[i - 1].at(5)) {
                allObjectsSorted = false;
                tempObjectData = ObjectData[i - 1];
                ObjectData[i - 1] = ObjectData[i];
                ObjectData[i] = tempObjectData;
            }
        }
    }
    for (int i = 0; i < numObjects; i++) {
        if (ObjectData[i].at(3).toFloat() < minX) {
            minX = ObjectData[i].at(3).toFloat();
        }
        if (ObjectData[i].at(3).toFloat() + ObjectData[i].at(1).toFloat() > maxX) {
            maxX = ObjectData[i].at(3).toFloat() + ObjectData[i].at(1).toFloat();
        }
    }
    mapSize = maxX - minX;
    countChunks = qCeil(qreal(mapSize / chunkSize));
    qDebug() << "mapSize =" << mapSize;
    qDebug() << "countChunks =" << countChunks;
    //ChunkList->resize(countChunks);
    qDebug() << "ChunkSize Vector size =" << ChunkList->size();
    for (int i = 0; i < numObjects; i++) {
        qDebug() << ObjectData[i];
    }
    for (int i = 0; i < numObjects; i++) {
        if (ObjectData[i].at(6).contains("no")) {
            qDebug() << "i =" << i;
            float endX = ObjectData[i].at(3).toFloat() + ObjectData[i].at(1).toFloat(); //конец X координаты объекта
            qDebug() << "startJ =" << qCeil(qreal(ObjectData[i].at(3).toFloat() / chunkSize));
            qDebug() << "endJ =" << qCeil(qreal(endX / chunkSize));
            for (int j = qCeil(qreal(ObjectData[i].at(3).toFloat() / chunkSize));
                 j <= qCeil(qreal(endX / chunkSize)); j++) {
                qDebug() << "j =" << j;
                ChunkList[j].push_back(i);
            }
        }
    }
    for (int i = 0; i < countChunks; i++) {
        qDebug() << "ChunkList[" << i << "] =" << ChunkList[i];
    }
}
