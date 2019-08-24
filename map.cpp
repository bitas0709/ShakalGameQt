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
                        ObjectData[numObject].push_back(buff.split("type:").at(1));
                    } else if (buff.contains("sizeX:")) {
                        ObjectData[numObject].push_back(buff.split("sizeX:").at(1));
                    } else if (buff.contains("sizeY:")) {
                        ObjectData[numObject].push_back(buff.split("sizeY:").at(1));
                    } else if (buff.contains("startX:")) {
                        ObjectData[numObject].push_back(buff.split("startX:").at(1));
                    } else if (buff.contains("startY:")) {
                        ObjectData[numObject].push_back(buff.split("startY:").at(1));
                    } else if (buff.contains("passable:")) {
                        ObjectData[numObject].push_back(buff.split("passable:").at(1));
                    } else if (buff.contains("texture:")) {
                        ObjectData[numObject].push_back(buff.split("texture:").at(1));
                    }
                } else {
                    readingObjectData = false;
                    numObject++;
                }
            }
        }
    }
    for (int i = 0; i < numObjects; i++) {
        qDebug() << ObjectData[i];
    }
    map.close();

}
