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
    QImage* image = new QImage(event->size().width(), event->size().height(), QImage::Format_RGB32);
    image->fill(WHITE.rgba());
    
    if (event->size().height() > event->oldSize().height() && event->size().width() > event->oldSize().width())
    {
        //making the canvas bigger
        for (int x = 0; x < event->oldSize().width(); ++x)
        {
            for (int y = 0; y < event->oldSize().height(); ++y)
            {
                image->setPixel(x, y, _image->pixel(x, y));
            }
        }
    }
    else
    {
        //making the canvas smaller
        for (int x = 0; x <= event->size().width(); ++x)
        {
            for (int y = 0; y <= event->size().height(); ++y)
            {
                image->setPixel(x, y, _image->pixel(x, y));
            }
        }
    }
    delete(this->_image);
    this->_image = image;
}

void PaintWidget::save(QString filename)
{
    this->_image->save(filename);
}

PaintWidget::~PaintWidget()
{
    delete this->_image;
}
