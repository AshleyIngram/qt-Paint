#include "Line.h"
#include <qwidget.h>
#include <QMouseEvent>
#include <math.h>
#include <qpainter.h>

using namespace std;

Line::Line(QImage* image, QColor* color, QWidget* parent)
{
    _image = image;
    _color = color;
    _parent = parent;
    _range = 5;
    _selected = -1;
    this->_unselected_icon = new QImage("./Images/line_unselected.jpg");
    this->_selected_icon = new QImage("./Images/line_selected.jpg");
    
    for (int i = 0; i < 4; ++i)
    {
        int p = 50 + 100 * i;
        _points[i] = QPoint(p, p);
        this->drawPoint(p, p, false);
    }
    
    for (int i = 0; i < 3; ++i)
    {
        this->drawLine(i, *_color);
    }
    
    _parent->repaint();
}

void Line::mousePressEvent(QMouseEvent* event)
{
    int a = event->x();
    int b = event->y();
    this->_selected = -1;
    
    for (int i = 0; i < 4; ++i)
    {
        //for every point
        QPoint p = _points[i];
        if (a > p.x() - _range && a < p.x() + _range && b > p.y() - _range && b < p.y() + _range)
        {
            this->drawPoint(p.x(), p.y(), true);
            this->_selected = i;
        }
    }
    
    for (int i = 0; i < 4; ++i)
    {
        if (_selected != i)
        {
            QPoint p = _points[i];
            this->drawPoint(p.x(), p.y(), false);
        }
    }
    
}
void Line::mouseMoveEvent(QMouseEvent* event)
{
    if (_selected == -1) return;
    
    if (event->x() > _image->width() || event->x() < 0 || event->y() > _image->height() || event->y() < 0)
    {
        return;
    }
    
    QPoint* p = &_points[_selected];
    this->removePoint(p->x(), p->y()); //get rid of the old one...
    
    //get rid of the old lines
    if (_selected != 0)
    {
        this->drawLine(_selected-1 , QColor("white"));
    }
    this->drawLine(_selected, QColor("white")); 
    
    p->setX(event->x());
    p->setY(event->y());
    this->drawPoint(p->x(), p->y(), true);
    
    //redraw lines
    if (_selected != 0)
    {
        this->drawLine(_selected-1 , *_color);
    }
    if (_selected != 3)
    {
        this->drawLine(_selected, *_color);
    }
}
void Line::mouseReleaseEvent(QMouseEvent* event)
{
    if (_selected == -1) return;
    
    QPoint p = _points[_selected];
    this->drawPoint(p.x(), p.y(), true);
}
void Line::updateImage(QImage* image)
{
    _image = image;
}

void Line::drawPoint(int x, int y, bool focus)
{
    QPainter painter(_image);
    
    QImage* image;
    if (!focus)
    {
        image = _unselected_icon;
    }
    else
    {
        image = _selected_icon;
    }
    int widthOffset = image->width()/2;
    int heightOffset = image->height()/2;
    
    QPoint imageOrigin(x - widthOffset, y - heightOffset);
    painter.drawImage(imageOrigin, *image);
}

void Line::removePoint(int x, int y)
{
    QPainter painter(_image);
    
    QImage* image = new QImage(5, 5, QImage::Format_RGB32);
    image->fill(QColor("white").rgba());
    int widthOffset = image->width()/2;
    int heightOffset = image->width()/2;
    
    QPoint imageOrigin(x - widthOffset, y - heightOffset);
    painter.drawImage(imageOrigin, *image);
}

void Line::drawLine(int point, QColor color)
{
    QPoint* p = &_points[point];
    QPoint* q = &_points[point + 1];
    
    for (double t = 0.0; t <= 1.0; t += 0.00001)
    {
        int dx = round(p->x() + (q->x() - p->x()) * t);
        int dy = round(p->y() + (q->y() - p->y()) * t);
        _image->setPixel(dx, dy, color.rgb());
    }
}

void Line::updateColor(QColor* color)
{
    this->_color = color;
}
