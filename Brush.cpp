#include "Brush.h"
#include <qwidget.h>
#include <QMouseEvent>

Brush::Brush(QImage* image, QColor color)
{
    this->_image = image;
    this->_color = color;
}

void Brush::mousePressEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::mouseMoveEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::mouseReleaseEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::paintArea(int x, int y)
{
    //currently painting a 3x3 box with the click in the middle. Change?
    for(int i = x-1; i <= x+1; i++)
    {
        for (int j = y-1; j < y+1; j++)
        {
            if (this->_image->height() > y && this->_image->width() > x && y > 0 && x > 0)
            {
                this->_image->setPixel(i, j, this->_color.rgba());
            }
        }
    }
}

void Brush::updateImage(QImage* image)
{
    this->_image = image;
}