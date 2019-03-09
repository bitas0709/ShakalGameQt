#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    //connect(timer, SIGNAL(timeout()), this, SLOT(movep()));
    //timer->start(time);
}

void MainWindow::initializeGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); //заливка всего окна белым непрозрачным фоном
    glEnable(GL_BLEND);
    m_player = new player();
    //connect(m_player->timer, SIGNAL(timeout()), this, SLOT(movep()));
}

void MainWindow::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, 1.0, 0.0); //задание размеров всего окна
    glViewport(0, 0, w, h);
}

void MainWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBackground();
    drawStat();
    if (actCheat) {
        drawActivatedCheat();
    }
    if (win) {
        drawWinMessage();
    }

    drawp();
}






void MainWindow::drawp() {
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0); //выбор чёрного цвета
    glVertex2f(10 + x, 10 + y); //левый верхний угол
    glVertex2f(20 + x, 10 + y); //правый верхний угол
    glVertex2f(20 + x, 20 + y); //правый нижний угол
    glVertex2f(10 + x, 20 + y); //левый нижний угол
    glEnd();
}

void MainWindow::drawStat() {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(playgroundWidth, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(playgroundWidth, windowHeight);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    QGLWidget::renderText(playgroundWidth + 10, 30 , 0, QString::fromUtf8("Вы набрали %1 очков:").arg(score), QFont());
    if (!win) {
        if (score >= 100) {
            win = true;
        }
    }
}

void MainWindow::drawWinMessage() {
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    glBegin(GL_POLYGON);
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glVertex2f(centerX - 100, centerY - 30);
    glVertex2f(centerX + 100, centerY - 30);
    glVertex2f(centerX + 100, centerY + 30);
    glVertex2f(centerX - 100, centerY + 30);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    QGLWidget::renderText(centerX - 40, centerY + 5 , 0, QString::fromUtf8("Вы выиграли!"), QFont());
}

void MainWindow::drawActivatedCheat() {
    glColor3f(1.0, 1.0, 1.0);
    QGLWidget::renderText(playgroundWidth + 10, windowHeight - 30 , 0, QString::fromUtf8("Чит-код активирован!"), QFont());
}

void MainWindow::drawBackground() {
    int blkSizeX = playgroundWidth / 100; //рассчёт размера пикселя заднего фона по X
    int blkSizeY = playgroundHeight / 100; //рассчёт размера пикселя заднего фона по Y
    bool evenX = true, evenY = true; //проверка на чётность
    for (int i = 0; i < playgroundHeight; i+=blkSizeY) {
        if(evenY) {
            for (int j = 0; j < playgroundWidth; j+=blkSizeX) {
                if(evenX) {
                    glBegin(GL_QUADS);
                    glColor3d(0.0, 1.0, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + blkSizeX, i);
                    glVertex2f(j + blkSizeX, i + blkSizeY);
                    glVertex2f(j, i + blkSizeY);
                    glEnd();
                    evenX = false;
                } else {
                    glBegin(GL_QUADS);
                    glColor3d(0.0, 0.8, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + blkSizeX, i);
                    glVertex2f(j + blkSizeX, i + blkSizeY);
                    glVertex2f(j, i + blkSizeY);
                    glEnd();
                    evenX = true;
                }
            }
            evenY = false;
        } else {
            for (int j = 0; j < playgroundWidth; j+=blkSizeX) {
                if(evenX) {
                    glBegin(GL_QUADS);
                    glColor3d(0.0, 0.8, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + blkSizeX, i);
                    glVertex2f(j + blkSizeX, i + blkSizeY);
                    glVertex2f(j, i + blkSizeX);
                    glEnd();
                    evenX = false;
                } else {
                    glBegin(GL_QUADS);
                    glColor3f(0.0, 1.0, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + blkSizeX, i);
                    glVertex2f(j + blkSizeX, i + blkSizeY);
                    glVertex2f(j, i + blkSizeY);
                    glEnd();
                    evenX = true;
                }
            }
            evenY = true;
        }
    }
}

void MainWindow::movep() {
    if (!win) {
        switch(key) {
        case 16777234: //Код нажатия на левую стрелку
            if (x > 0) {
                x -= 2;
            }
            break;
        case 16777235: //Код нажатия на стелку вверх
            if (y > 2) {
                y -= 2;
            }
            break;
        case 16777236: //Код нажатия на правую стрелку
            if (x < playgroundWidth - 40) {
                x += 2;
            }
            break;
        case 16777237: //Код нажатия на клавишу вниз
            if (y < playgroundHeight - 40) {
                y += 2;
            }
            break;
        }
    }
    QGLWidget::updateGL();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (cheat.size() == 20) {
        cheat.remove(0, 10);
    }
    if (!event->isAutoRepeat()) {
        switch (event->key()) {
        case Qt::Key_Left:
            //m_player->timer->start(m_player->time);
            movep();
            key = int(event->key());
            break;
        case Qt::Key_Right:
            //m_player->timer->start(m_player->time);
            movep();
            key = int(event->key());
            break;
        case Qt::Key_Up:
            //m_player->timer->start(m_player->time);
            movep();
            key = int(event->key());
            break;
        case Qt::Key_Down:
            //m_player->timer->start(m_player->time);
            movep();
            key = int(event->key());
            break;
        case Qt::Key_Space:
            score++;
            break;
        case Qt::Key_A:
            cheat.append("a");
            break;
        case Qt::Key_B:
            cheat.append("b");
            break;
        case Qt::Key_C:
            cheat.append("c");
            break;
        case Qt::Key_D:
            cheat.append("d");
            break;
        case Qt::Key_E:
            cheat.append("e");
            break;
        case Qt::Key_F:
            cheat.append("f");
            break;
        case Qt::Key_G:
            cheat.append("g");
            break;
        case Qt::Key_H:
            cheat.append("h");
            break;
        case Qt::Key_I:
            cheat.append("i");
            break;
        case Qt::Key_J:
            cheat.append("j");
            break;
        case Qt::Key_K:
            cheat.append("k");
            break;
        case Qt::Key_L:
            cheat.append("l");
            break;
        case Qt::Key_M:
            cheat.append("m");
            break;
        case Qt::Key_N:
            cheat.append("n");
            break;
        case Qt::Key_O:
            cheat.append("o");
            break;
        case Qt::Key_P:
            cheat.append("p");
            break;
        case Qt::Key_Q:
            cheat.append("q");
            break;
        case Qt::Key_R:
            cheat.append("r");
            break;
        case Qt::Key_S:
            cheat.append("s");
            break;
        case Qt::Key_T:
            cheat.append("t");
            break;
        case Qt::Key_U:
            cheat.append("u");
            break;
        case Qt::Key_V:
            cheat.append("v");
            break;
        case Qt::Key_W:
            cheat.append("w");
            break;
        case Qt::Key_X:
            cheat.append("x");
            break;
        case Qt::Key_Y:
            cheat.append("y");
            break;
        case Qt::Key_Z:
            cheat.append("z");
            break;
        }
    }
    if (cheat.indexOf("letmewin", 0) == 0) {
        win = true;
        actCheat = true;
        cheat.clear();
    } else if (cheat.indexOf("fastfastfast", 0) == 0) {
        time = 10;
        timer->start(time);
        actCheat = true;
        cheat.clear();
    } else if (cheat.indexOf("dragonforce", 0) == 0) {
        actCheat = true;
        time = 1;
        timer->start(time);
        //qDebug() << "DRAGONFORCE!!!";
        QSound::play(":/resources/music/dragonforce.wav");
        cheat.clear();
    }
    //qDebug().noquote() << "cheat =" << cheat;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        //m_player->timer->stop();
        key = 0;
    }
}

MainWindow::~MainWindow()
{

}

//систему работы с файлами нужно доработать для лучшей читаемости

/*settings.setFileName("settings.inf");
if (settings.exists()) {
    if (!settings.open(QIODevice::ReadOnly)) {
        qDebug() << "Ошибка чтения файла с настройками!";
    } else {
        QStringList settlist; //список переменных, полученных из файла
        QStringList settval; //значения переменных, полученных из файла
        while(!settings.atEnd()) {
            QString line = settings.readLine(); //считывает строку из файла
            QStringList list = line.split(" "); //разделение строки на слова, разделённые пробелом
            settlist.append(list.at(0));
            settval.append(list.at(2));
        }
        settlist.append("eof");
        for(int i = 0; i < settlist.indexOf("eof"); i++) {
            qDebug().noquote() << settlist.at(i) << "=" << settval.at(i);
        }
        switch(settlist.indexOf("eof")) {
        case 0: //fullscreen
        }
    }
} else {
    qDebug() << "Файл настроек не существует!";
}
settings.close();*/
/*static const int coord[1][4][3] = {
    { {10, 10, 0}, {20, 10, 0}, {20, 20, 0}, {10, 20, 0} }
};*/
