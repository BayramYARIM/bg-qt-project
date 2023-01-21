#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <myimage.h>
#include <circleimage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int _Width, _Height;
    QLabel *bg;
    QLabel *lblMagnet;
    QLabel *lblGameScore;
    MyImage *ti;
    CircleImage *ci;
    QList<MyImage *> ListImages;
    QList<CircleImage *> ListCircle;

    QTimer *tmrCreate, *tmrMoved;
    void winController();
    int destroyCircleCount, sumStarCount, GameScore;
    int speedCount;

private slots:
    void createImages();
    void movedImages();
    void getCircleID();
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
