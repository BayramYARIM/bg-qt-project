#include "myimage.h"
int MyImage::destroyCnt = 0;
int MyImage::objectID = 0;


MyImage::MyImage(QWidget *parent)
{
    int x = QRandomGenerator::global()->bounded(0, dw.width()-150);
    int y = QRandomGenerator::global()->bounded(0, dw.height()-150);

    setParent(parent);
    setFixedWidth(90);
    setFixedHeight(90);
    move(x,y);
    m_color = QRandomGenerator::global()->generate();
    m_image = QImage(75,75, QImage::Format_ARGB32);
    createImage();
    setPixmap(QPixmap::fromImage(this->m_image));
    show();
    m_state = false;
    setObjectName(QString("m_img%1").arg(objectID++));
    setAlignment(Qt::AlignCenter);
//    setStyleSheet("background-color: grey;");
}

ImgType MyImage::getType() const
{
    return m_type;
}

void MyImage::createImage()
{
    m_type = (ImgType)QRandomGenerator::global()->bounded(0,4);

    switch (m_type) {
    case imgRectangle:
        m_lp.append(QPoint(5,35));
        m_lp.append(QPoint(50,35));
        m_lp.append(QPoint(50,70));
        m_lp.append(QPoint(5,70));
        m_lp.append(QPoint(5,35));
        for(int i=0; i<m_lp.length()-1; i++){
            drawImage(m_lp[i], m_lp[i+1]);
        }
        break;
    case imgTriangle:
            m_lp.append(QPoint(5,5));
            m_lp.append(QPoint(55,5));
            m_lp.append(QPoint(30,30));
            m_lp.append(QPoint(5,5));
            for(int i=0; i<m_lp.length()-1; i++){
                drawImage(m_lp[i], m_lp[i+1]);
            }
            fillImage(30,16, m_color, m_color);
        break;

    case imgSquare:
            m_lp.append(QPoint(0,35));
            m_lp.append(QPoint(35,35));
            m_lp.append(QPoint(35,70));
            m_lp.append(QPoint(0,70));
            m_lp.append(QPoint(0,35));
            for(int i=0; i<m_lp.length()-1; i++){
                drawImage(m_lp[i], m_lp[i+1]);
            }
            //fillImage(m_lp[0].x(),m_lp[0].y(), m_color, m_color);
        break;

    case imgStar:
            m_lp.append(QPoint(18,10));
            m_lp.append(QPoint(8,25));
            m_lp.append(QPoint(33,25));
            m_lp.append(QPoint(7,5));
            m_lp.append(QPoint(20,35));
            m_lp.append(QPoint(23,8));
            m_lp.append(QPoint(18,10));

            for(int i=0; i<m_lp.length()-1; i++){
                drawImage(m_lp[i], m_lp[i+1]);
            }
            //fillImage(m_lp[0].x(),m_lp[0].y(), m_color, m_color);
        break;
    }
}


void MyImage::drawImage(QPoint start, QPoint stop)
{
    double dx = stop.x() - start.x();
    double dy = stop.y() - start.y();
    double xinc, yinc, step, x,y;

    if(fabs(dx)>fabs(dy)){
        step=fabs(dx);
    }
    else{
        step=fabs(dy);
    }
    xinc=dx/step;
    yinc=dy/step;
    x=start.x();
    y=start.y();

    for(int i=0; i<step; i++)
    {
        x+=xinc;
        y+=yinc;
        m_image.setDotsPerMeterX(5);
        m_image.setDotsPerMeterY(5);
        m_image.setPixel(round(x),round(y), m_color);
    }
}

void MyImage::fillImage(int x, int y, QRgb backgroundColor, QRgb foregroundColor)
{
    if(m_image.pixel(x,y)!=backgroundColor){

        m_image.setPixel(x,y,foregroundColor);
        fillImage(x+1, y, backgroundColor, foregroundColor);
        fillImage(x-1, y, backgroundColor, foregroundColor);
        fillImage(x, y+1, backgroundColor, foregroundColor);
        fillImage(x, y-1, backgroundColor, foregroundColor);
    }
}

void MyImage::scaleImage()
{
    QPixmap qpix(QApplication::applicationDirPath()+"/objBack.png");
    QImage myimg=qpix.toImage();
    int x,y;
    double sx=0.1, sy=0.1;
    for(int i=0; i<60; i++){
        for(int j=0; j<60; j++){
            x=i*sx; y=j*sy;
            myimg.setPixel(x, y, m_image.pixel(i,j));
        }
    }
    setPixmap(QPixmap::fromImage(myimg));
}

void MyImage::rotateImage()
{
    double x,y;
    double angle = 3;
    QImage canvas;

    qDebug() << "Rotate::Begin";

    for(int i=0; i<m_image.width(); i++){

        for(int j=0; j<m_image.height(); j++){

            x = i*cos(qDegreesToRadians(angle)) - j*sin(qDegreesToRadians(angle));
            y = i*sin(qDegreesToRadians(angle)) + j*cos(qDegreesToRadians(angle));
            canvas.setPixel(round(x)+m_image.width()+(width())/8, round(y)+m_image.height()+(height())/8, m_image.pixel(i,j));
        }
    }
    setPixmap(QPixmap::fromImage(canvas));
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    qDebug() << "Rotate::End";
}


void MyImage::moveImage()
{
//    int ax, ay;
//    ax = QRandomGenerator::global()->bounded(90, dw.width()-90);
//    ay = QRandomGenerator::global()->bounded(90, dw.height()-90);
    if (m_state == false)
    {
        move(pos().x(), pos().y()+5);
        if (pos().y() > dw.height()-100){
            this->destroyCnt += 1;
            m_state = true;
            hide();
            destroy();
        }
    }
    update();
    repaint();
}

MyImage::~MyImage()
{
//    this->Coordinate = 0;
//    this->m_label = NULL;
}
