#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QRandomGenerator>
#include <QApplication>
#include <QLabel>
#include <QtMath>
#include <QDebug>
#include <QDesktopWidget>

enum ImgType{
    imgRectangle,
    imgTriangle,
    imgSquare,
    imgStar,
};

class MyImage : public QLabel
{
    Q_OBJECT
private:
    bool    m_state;
    ImgType m_type;
    QPoint  m_point;
    QRgb    m_color;
    QImage  m_image;
    QDesktopWidget dw;
    QList<QPoint> m_lp;

    void createImage();
    void drawImage(QPoint start, QPoint stop);
    void fillImage(int x, int y, QRgb backgroundColor, QRgb foregroundColor);

public:
    MyImage(QWidget *parent=nullptr); //Constructor
    ~MyImage();//Destructor
    void moveImage();
    void scaleImage();
    void rotateImage();
    static int destroyCnt;
    static int objectID;
    ImgType getType() const;
};

#endif // MYIMAGE_H
