#include "Line.h"
#include <qwidget.h>
#include <QMouseEvent>
#include <math.h>
#include <qpainter.h>

Line::Line(QImage* image, QColor* color, QWidget* parent) : BaseLine(image, color, parent)
{
    //TODO: Change this for variable number of points
    for (int i = 0; i < 3; ++i)
    {
        this->drawLine(i, *_color);
    }
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