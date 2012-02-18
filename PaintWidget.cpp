#include "PaintWidget.h"
#include <qwidget.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <QResizeEvent>

const QColor WHITE("white");
const QColor BLACK("black");
const QColor RED("red");

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent)
{
    this->_image = new QImage(512, 512, QImage::Format_RGB32); //size of image
    _image->fill(WHITE.rgba());
    this->_color = BLACK;
}

PaintWidget::PaintWidget(QString filename, QWidget* parent) : QWidget(parent)
{
    this->_image = new QImage(512, 512, QImage::Format_RGB32);
    _image->load(filename);
    this->_color = BLACK;
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
    //QWidget Redraw event
    QPainter painter(this);
    
    QPointF imageOrigin(0.0, 0.0);
    painter.drawImage(imageOrigin,  *_image);
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void PaintWidget::paintArea(int x, int y)
{
    //currently painting a 3x3 box with the click in the middle. Change?
    for(int i = x-1; i <= x+1; i++)
    {
        for (int j = y-1; j < y+1; j++)
        {
            this->_image->setPixel(i, j, this->_color.rgba());
        }
    }
    this->repaint();
}

void PaintWidget::resizeEvent(QResizeEvent* event)
{
    *_image = this->_image->copy(0, 0, event->size().width(), event->size().height());
    for (int x = 0; x <= event->size().width(); ++x)
    {
        for (int y = 0; y <= event->size().height(); ++y)
        {
            //if the pixel is black and off the bounds of the image pre-resize...
            if(this->_image->pixel(x, y) == this->_color.rgba()) 
            {
               if (y >= event->oldSize().height() || x >= event->oldSize().width())
               {
                    //...make it white
                    this->_image->setPixel(x, y, WHITE.rgba());
                    //This stops it from recolouring valid squiggles
               }
            }
        }
    }
}

void PaintWidget::save(QString filename)
{
    this->_image->save(filename);
}

PaintWidget::~PaintWidget()
{
    delete this->_image;
}