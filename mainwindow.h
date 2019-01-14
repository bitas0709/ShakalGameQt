#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGLWidget>
#include <QtOpenGL>
#include <QDebug>
#include <QString>
#include <QSound>
#include <QScreen>

//QRect *screenRect = QApplication::screens().at(0)->geometry();      для считывания разрешения первого экрана, но это не точно

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    //~MainWindow();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    int playgroundWidth = 600, playgroundHeight = 600; //размеры игрового поля x и y
    int windowWidth = playgroundWidth + 200, windowHeight = playgroundHeight; //размеры окна x и y
    //int borderX = 10, borderY = 10; //размер рамок

    void drawBackground(); //отрисовка заднего фона игрового поля
    void drawp(); //отрисовка модели игрока
    void drawStat(); //отрисовка статистики игры
    void drawWinMessage(); //отрисовка окна с сообщением о выигрыше
    void drawActivatedCheat(); //отрисовка окна о вводе чит-кода

    QFont msgText(); //шрифт сообщений

    int x = 0, y = 0; //стартовые координаты модели игрока
    qint8 score = 0; //счёт игрока

    virtual void keyPressEvent(QKeyEvent *event); //обработка событий клавиатуры
    virtual void keyReleaseEvent(QKeyEvent *event);
    int key; //код нажатой клавиши

    bool win = false; //вывод текста о выигрыше на экран
    bool actCheat = false;

    QString cheat; //строка для обработки ввода читов

    QTimer *timer = new QTimer(this);
    int time = 500; //скорость движения игрока

    QFile settings; //файл с настройками игры
signals:
    void signalmove(QString key); //сигнал для перемещения игрока

protected slots:
    void movep(); //слот для перемещения игрока
};

#endif // MAINWINDOW_H
