#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(this, SIGNAL(signalmove(QString)), this, SLOT(movep(QString)));
    timer->start(2000);
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
    glVertex2f(1 + x, 1 + y);
    glVertex2f(2 + x, 1 + y);
    glVertex2f(2 + x, 2 + y);
    glVertex2f(1 + x, 2 + y);
    glEnd();
}

void MainWindow::movep(QString key) {
    qDebug() << "Hehmda";
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    //qDebug() << "Hehmda";
    int hehmda = 0;
    if (cheat.size() == 20) {
        cheat.remove(0, 10);
    }
    switch (event->key()) {
    case Qt::Key_Left:
        hehmda = int(Qt::Key_Left);
        qDebug() << "Left =" << hehmda;
        //qDebug() << "Hehmda, LeftArrow";
        if (x > 0) {
            x -= 0.2;
        }
        break;
    case Qt::Key_Right:
        qDebug() << "Hehmda, RightArrow";
        if (x < windowWidth - 0.3) {
            x += 0.2;
        }
        break;
    case Qt::Key_Up:
        qDebug() << "Hehmda, UpArrow";
        if (y > 0.2) {
            y -= 0.2;
        }
        break;
    case Qt::Key_Down:
        qDebug() << "Hehmda, DownArrow";
        if (y < windowHeight) {
            y += 0.2;
        }
        break;
    case Qt::Key_Space:
        qDebug() << "Hehmda, SpaceBar";
        score++;
        break;
    case Qt::Key_E:
        qDebug() << "Hehmda, E";
        cheat.append("e");
        break;
    case Qt::Key_I:
        qDebug() << "Hehmda, I";
        cheat.append("i");
        break;
    case Qt::Key_L:
        qDebug() << "Hehmda, L";
        cheat.append("l");
        break;
    case Qt::Key_M:
        qDebug() << "Hehmda, M";
        cheat.append("m");
        break;
    case Qt::Key_N:
        qDebug() << "Hehmda, N";
        cheat.append("n");
        break;
    case Qt::Key_T:
        qDebug() << "Hehmda, T";
        cheat.append("t");
        break;
    case Qt::Key_W:
        qDebug() << "Hehmda, W";
        cheat.append("w");
        break;
    }
    //qDebug() << "Cheat:" << cheat;
    if (cheat.indexOf("letmewin", 0) == 0) {
        win = true;
    }
    QGLWidget::updateGL();
}

/*MainWindow::~MainWindow()
{

}*/
