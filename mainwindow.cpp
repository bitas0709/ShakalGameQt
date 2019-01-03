#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(movep()));
    timer->start(time);
}

void MainWindow::initializeGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void MainWindow::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, 1.0, 0.0);
    //glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void MainWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(windowWidth, 0.0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0.0, windowHeight);
    glEnd();*/
    for (float i = 0.0; i < windowHeight; i+=0.1) {
        if(int(i*10)%2 == 0) {
            for (float j = 0.0; j < windowWidth; j+=0.1) {
                if(int(j*10)%2 == 0) {
                    glBegin(GL_QUADS);
                    glColor3f(0.0, 1.0, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + 0.1, i);
                    glVertex2f(j + 0.1, i + 0.1);
                    glVertex2f(j, i + 0.1);
                    glEnd();
                } else {
                    glBegin(GL_QUADS);
                    glColor3f(0.0, 0.8, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + 0.1, i);
                    glVertex2f(j + 0.1, i + 0.1);
                    glVertex2f(j, i + 0.1);
                    glEnd();
                }
            }
        } else {
            for (float j = 0.0; j < windowWidth; j+=0.1) {
                if(int(j*10)%2 == 0) {
                    glBegin(GL_QUADS);
                    glColor3f(0.0, 0.8, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + 0.1, i);
                    glVertex2f(j + 0.1, i + 0.1);
                    glVertex2f(j, i + 0.1);
                    glEnd();
                } else {
                    glBegin(GL_QUADS);
                    glColor3f(0.0, 1.0, 0.0);
                    glVertex2f(j, i);
                    glVertex2f(j + 0.1, i);
                    glVertex2f(j + 0.1, i + 0.1);
                    glVertex2f(j, i + 0.1);
                    glEnd();
                }
            }
        }
    }
    glColor3f(0.0, 0.0, 0.0);
    QGLWidget::renderText(7, windowHeight - 0.5 , 0, QString::fromUtf8("Вы набрали %1 очков:").arg(score), QFont());
    if (win) {
        QGLWidget::renderText(5, 5 , 0, QString::fromUtf8("Вы выиграли!"), QFont());
    }
    mainp();
}

void MainWindow::mainp() {
    /*glBegin(GL_TRIANGLES);
    glVertex2d(x + 0.1, windowHeight - y);
    glVertex2d(x, windowHeight -  y + 0.2);
    glVertex2d(x + 0.2, windowHeight - y + 0.2);
    glEnd();*/
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(1 + x, 1 + y);
    glVertex2f(2 + x, 1 + y);
    glVertex2f(2 + x, 2 + y);
    glVertex2f(1 + x, 2 + y);
    glEnd();
}

void MainWindow::movep() {
    //qDebug() << "Tick";
    if (!win) {
        switch(key) {
        case 16777234: //Код нажатия на левую стрелку
            if (x > 0) {
                x -= 0.2;
            }
            break;
        case 16777235: //Код нажатия на стелку вверх
            if (y > 0.2) {
                y -= 0.2;
            }
            break;
        case 16777236: //Код нажатия на правую стрелку
            if (x < windowWidth - 0.3) {
                x += 0.2;
            }
            break;
        case 16777237: //Код нажатия на клавишу вниз
            if (y < windowHeight) {
                y += 0.2;
            }
            break;
        }
    }
    key = 0;
    QGLWidget::updateGL();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (cheat.size() == 20) {
        cheat.remove(0, 10);
    }
    switch (event->key()) {
    case Qt::Key_Left:
        key = int(event->key());
        break;
    case Qt::Key_Right:
        key = int(event->key());
        break;
    case Qt::Key_Up:
        key = int(event->key());
        break;
    case Qt::Key_Down:
        key = int(event->key());
        break;
    case Qt::Key_Space:
        score++;
        break;
    case Qt::Key_A:
        cheat.append("a");
        break;
    case Qt::Key_E:
        cheat.append("e");
        break;
    case Qt::Key_F:
        cheat.append("f");
        break;
    case Qt::Key_I:
        cheat.append("i");
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
    case Qt::Key_S:
        cheat.append("s");
        break;
    case Qt::Key_T:
        cheat.append("t");
        break;
    case Qt::Key_W:
        cheat.append("w");
        break;
    }
    //qDebug() << "Cheat:" << cheat;
    if (cheat.indexOf("letmewin", 0) == 0) {
        win = true;
    } else if (cheat.indexOf("fastfastfast", 0) == 0) {
        time = 10;
        timer->start(time);
    }
}

/*MainWindow::~MainWindow()
{

}*/
