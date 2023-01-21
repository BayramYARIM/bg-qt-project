#include "circleimage.h"
#include <QDebug>

int CircleImage::objectID = 0;

CircleImage::CircleImage(QWidget *parent)
{
    int x = QRandomGenerator::global()->bounded(0, dw.width()-200);
    int y = QRandomGenerator::global()->bounded(0, dw.height()-200);
    setParent(parent);
    setFixedWidth(180);
    setFixedHeight(180);
    //setStyleSheet("background-color:grey;");
    move(x,y);
    m_color = QRandomGenerator::global()->generate();
    m_image = QImage(180,180, QImage::Format_ARGB32);
    m_time = QDateTime::currentSecsSinceEpoch();
    drawCircle();
    setPixmap(QPixmap::fromImage(this->m_image));
    setStyleSheet(QString("background-color:transparent; border-radius:%1px;").arg(getID()));
    setObjectName(QString("circle%1").arg(objectID++));
    show();
}

CircleImage::~CircleImage()
{
    this->ID = 1;
}

void CircleImage::moveCircle()
{
    move(this->pos().x(), this->pos().y()+5);
}

void CircleImage::destroyCircle()
{
    this->ID = -1;
    this->hide();
}

void CircleImage::mvImage(QPoint qp)
{
    QPoint mp = pos(); //Varolan konum
    int diffX, diffY;
    diffX = qp.x() - mp.x();
    diffY = qp.y() - mp.y();
    for (int j=0; j<1000; j++) {
        if ((mp.x() == qp.x()) || (mp.y() == qp.y()))
            break;
        move(mp.x()+5, mp.y()+5);
        QApplication::processEvents();
    }
    //move(this->pos().x(), this->pos().y()+5);
}

bool CircleImage::outOfScreen()
{
    if (pos().x() > (dw.height() + 50))
        return true;
    else
        return false;
}

qint64 CircleImage::getTime() const
{
    return m_time;
}

void CircleImage::drawCircle()
{
    unsigned int mx = QRandomGenerator::global()->bounded(50, 100);
    unsigned int my = QRandomGenerator::global()->bounded(40, 80);
    int mdiff = QRandomGenerator::global()->bounded(10, 50);
    //qDebug() << "Mx:" << mx << "My:" << my << "Diff:" << mdiff;

    pointFirst = QPoint(mx, my);
    pointSecond = QPoint(mx+mdiff, my);

    setID(mdiff);

    int radius = pointSecond.x() - pointFirst.x();

    if(radius < 0) radius = - radius;

    int x = radius;
    int y = 0;
    int mistakeValue = 0;
    int mistakeValueOne, mistakeValueTwo;

    int xCenter = pointFirst.x();
    int yCenter = pointFirst.y();

    pixelDrawer8(x, y, xCenter, yCenter);
    while(x >= y)
    {
        mistakeValueOne = mistakeValue + (2 * y + 1);
        mistakeValueTwo = mistakeValue + (2 * y + 1) - (2 * x - 1);
        if(abs(mistakeValueOne) < abs(mistakeValueTwo))
        {
            y++;
            mistakeValue = mistakeValueOne;
        }
        else
        {
            x--;
            y++;
            mistakeValue = mistakeValueTwo;
        }
        pixelDrawer8(x, y, xCenter, yCenter);
    }

    //m_label->setPixmap(QPixmap::fromImage(m_image));
    m_color = QRandomGenerator::global()->generate();
    fillCircle(pointFirst.x(), pointSecond.y(), m_image.pixel(pointFirst.x(), pointSecond.y()), m_color);
}

void CircleImage::pixelDrawer8(int x, int y, int xCenter, int yCenter)
{
    m_image.setPixel(round(xCenter + x),round(yCenter + y),m_color);
    m_image.setPixel(round(xCenter - x),round(yCenter + y),m_color);
    m_image.setPixel(round(xCenter + x),round(yCenter - y),m_color);
    m_image.setPixel(round(xCenter - x),round(yCenter - y),m_color);
    m_image.setPixel(round(xCenter + y),round(yCenter + x),m_color);
    m_image.setPixel(round(xCenter - y),round(yCenter + x),m_color);
    m_image.setPixel(round(xCenter + y),round(yCenter - x),m_color);
    m_image.setPixel(round(xCenter - y),round(yCenter - x),m_color);
}

void CircleImage::mousePressEvent(QMouseEvent *ev)
{
    emit m_clicked();
}

void CircleImage::setID(int id)
{
    this->ID = id;
}

int CircleImage::getID()
{
    return this->ID;
}

void CircleImage::fillCircle(int x, int y, QRgb backgroundColor, QRgb foregroundColor)
{
   if (m_image.pixel(x,y) == backgroundColor)
   {
       m_image.setPixel(x,y, foregroundColor);
       //m_label->setPixmap(QPixmap::fromImage(m_image));
       fillCircle(x+1, y, backgroundColor, foregroundColor);
       fillCircle(x-1, y, backgroundColor, foregroundColor);
       fillCircle(x, y+1, backgroundColor, foregroundColor);
       fillCircle(x, y-1, backgroundColor, foregroundColor);
   }
}
