#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGLWidget>
#include <QtOpenGL>
#include <QDebug>
#include <QString>

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
    void mainp(); //модель игрока
    int x = 0, y = 0; //стартовые координаты
    int windowWidth = 102, windowHeight = 102; //размеры окна x и y
    int borderX = 2, borderY = 2; //размер рамок
    virtual void keyPressEvent(QKeyEvent *event); //обработка событий клавиатуры
    bool win = false; //вывод текста о выигрыше на экран
    qint8 score = 0; //счёт игрока
    QString cheat; //строка для обработки ввода читов
    QTimer *timer = new QTimer(this);
    int key; //код нажатой клавиши
    int time = 500; //скорость движения игрока

signals:
    void signalmove(QString key); //сигнал для перемещения игрока

protected slots:
    void movep(); //слот для перемещения игрока
};

#endif // MAINWINDOW_H
