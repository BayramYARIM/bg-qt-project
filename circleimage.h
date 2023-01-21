#ifndef CIRCLEIMAGE_H
#define CIRCLEIMAGE_H

#include <QApplication>
#include <QObject>
#include <QLabel>
#include <QImage>
#include <QDesktopWidget>
#include <QRandomGenerator>
#include <QTime>

class CircleImage : public QLabel
{
    Q_OBJECT
public:
    explicit CircleImage(QWidget *parent = nullptr);
    ~CircleImage();
    void moveCircle();
    void destroyCircle();
    void mvImage(QPoint qp);
    bool outOfScreen();
    qint64 getTime() const;
    static int objectID;

private:
    QLabel *m_label;
    QPoint  m_point;
    QRgb    m_color;
    QPoint  pointFirst, pointSecond;
    QImage  m_image;
    QDesktopWidget dw;
    qint64 m_time;
    int ID;

    void createCircle();
    void drawCircle();
    void fillCircle(int x, int y, QRgb backgroundColor, QRgb foregroundColor);
    void pixelDrawer8(int x, int y, int xCenter, int yCenter);

signals:
    void m_clicked();

protected:
    void mousePressEvent(QMouseEvent *ev);

public slots:
    void setID(int id);
    int  getID();

};

#endif // CIRCLEIMAGE_H
