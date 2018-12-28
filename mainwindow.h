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
    double x = 0.0, y = 0.0; //стартовые координаты
    double windowWidth = 10.2, windowHeight = 10.2; //размеры окна x и y
    double borderX = 0.2, borderY = 0.2; //размер рамок
    virtual void keyPressEvent(QKeyEvent *event); //обработка событий клавиатуры
    bool win = false; //вывод текста о выигрыше на экран
    qint8 score = 0; //счёт игрока
    QString cheat; //строка для обработки ввода читов
    int key; //код нажатой клавиши

signals:
    void signalmove(QString key); //сигнал для перемещения игрока

protected slots:
    void movep(); //слот для перемещения игрока
};

#endif // MAINWINDOW_H
