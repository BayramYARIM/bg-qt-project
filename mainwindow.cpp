/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Bilgisayar Grafikleri - Grafik Oyun
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : mainwindow.cpp
 *  @Create  : 10.12.2022 21:48
 *  @Update  : 13.12.2022 19:53
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BILGISAYAR GRAFIKLERI - Bayram YARIM - 18010011067");
    QDesktopWidget dw;
    _Height = dw.height();//Screen Height -- Yukseklik
    _Width  = dw.width(); //Screen Width -- Genislik
    //setGeometry(0,0, _Width, _Height);

    destroyCircleCount=0;
    sumStarCount=0;
    GameScore=0;

    bg = new QLabel(this);
    bg->setGeometry(0,0, _Width, _Height);
    bg->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/res/bg4.jpg").scaled(dw.width(), dw.height())));

    lblGameScore = new QLabel(this);
    lblGameScore->setGeometry(100,0,dw.width()-200, 30);
    lblGameScore->setStyleSheet("color: black; font-size:24px;");
    lblGameScore->setAlignment(Qt::AlignCenter);
    lblGameScore->setText("Vurulan Balon: 0 | Toplanan Sekil: 0 | Kacan Sekil: 0 | PUAN: 0");

    lblMagnet = new QLabel(bg);
    lblMagnet->setGeometry(dw.width()/2, dw.height()-250,192,192);
    lblMagnet->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/res/upMagnet.png")).scaled(192,192,Qt::IgnoreAspectRatio));

    tmrCreate = new QTimer(this);
    connect(tmrCreate, SIGNAL(timeout()), this, SLOT(createImages()));
    tmrCreate->start(1000);

    tmrMoved = new QTimer(this);
    connect(tmrMoved, SIGNAL(timeout()), this, SLOT(movedImages()));
    tmrMoved->start(1000);

    speedCount = 10;

}

void MainWindow::createImages()
{
    ci = new CircleImage(bg);
    connect(ci, SIGNAL(m_clicked()), this, SLOT(getCircleID()));
    ListCircle.append(ci);

    ti = new MyImage(bg);
    ListImages.append(ti);
}

void MainWindow::movedImages()
{
    foreach (CircleImage *mci, ListCircle) {
        mci->moveCircle();
        if (QDateTime::currentSecsSinceEpoch() - mci->getTime() > 10){
            ListCircle.removeOne(mci);
            mci->hide();
        }
    }

    foreach (MyImage *mti, ListImages) {
        mti->moveImage();
    }

    winController();

    lblGameScore->setText(QString("Vurulan Balon: %1 | Toplanan Sekil: %2 | Kacan Sekil: %3 | PUAN: %4")
                          .arg(destroyCircleCount)
                          .arg(sumStarCount)
                          .arg(MyImage::destroyCnt)
                          .arg(GameScore));

    update();
    lblMagnet->update();
    lblMagnet->repaint();

    if (MyImage::destroyCnt >= 30)
    {
        tmrCreate->stop();
        tmrMoved->stop();
        QMessageBox msgBox;
        msgBox.setInformativeText("Oyun Bitti:\n"+lblGameScore->text());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}


void MainWindow::getCircleID()
{
    GameScore += ((CircleImage *) sender())->getID();
//    qDebug() << ((CircleImage *) sender())->getTime();
//    qDebug() << QDateTime::currentSecsSinceEpoch();
    ((CircleImage *) sender())->hide();
//    ((CircleImage *) sender())->mvImage(lblMagnet->pos());
    destroyCircleCount++;

    if (destroyCircleCount == 20)
    {
        tmrCreate->setInterval(750);
        tmrMoved->setInterval(750);
        speedCount = 15;
    }
    if (destroyCircleCount == 30)
    {
        tmrCreate->setInterval(500);
        tmrMoved->setInterval(500);
        speedCount = 20;
    }

    if (destroyCircleCount == 35)
    {
        tmrCreate->setInterval(250);
        tmrMoved->setInterval(250);

        speedCount = 25;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D :
    case Qt::Key_Right:
        //qDebug() << "Right-D";
//        lblMagnet->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/rightMagnet.png")).scaled(192,192,Qt::IgnoreAspectRatio));
        if (lblMagnet->pos().x() < _Width-180)
            lblMagnet->move(lblMagnet->pos().x()+speedCount, lblMagnet->pos().y());
        break;

    case Qt::Key_A :
    case Qt::Key_Left:
        //qDebug() << "Left-A";
//        lblMagnet->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/leftMagnet.png")).scaled(192,192,Qt::IgnoreAspectRatio));
        if (lblMagnet->pos().x() > 0)
            lblMagnet->move(lblMagnet->pos().x()-speedCount, lblMagnet->pos().y());
        break;

    case Qt::Key_S :
    case Qt::Key_Down :
        //qDebug() << "Down-S";
//        lblMagnet->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/downMagnet.png")).scaled(192,192,Qt::IgnoreAspectRatio));
        lblMagnet->move(lblMagnet->pos().x(), lblMagnet->pos().y()+speedCount);
        break;

    case Qt::Key_W :
    case Qt::Key_Up:
        //qDebug() << "Up-W";
//        lblMagnet->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/upMagnet.png")).scaled(192,192,Qt::IgnoreAspectRatio));
        lblMagnet->move(lblMagnet->pos().x(), lblMagnet->pos().y()-speedCount);
        break;

    case Qt::Key_Space:
        qDebug() << "SpaceClick!";
        break;
    }
    winController();
    update();
    repaint();
    bg->update();
    bg->repaint();
}

void MainWindow::winController()
{
    foreach (MyImage *mti, ListImages) {
        //mti->scaleImage();
        QRect aRect = lblMagnet->geometry();
        if (aRect.intersects(mti->geometry()))
        {
            switch (mti->getType()) {
            case imgRectangle :
                GameScore += 40;
                break;
            case imgTriangle :
                GameScore += 30;
//                mti->rotateImage();
                break;
            case imgSquare :
                GameScore += 20;
                break;
            case imgStar :
                GameScore += 50;
//                mti->rotateImage();
                break;
            }
            mti->hide();
            ListImages.removeOne(mti);
            sumStarCount++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

