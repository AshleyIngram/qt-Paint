#ifndef _LINE_H
#define _LINE_H 1

#include "ITool.h"
#include <qwidget.h>
#include <QMouseEvent>

class Line : public ITool
{  
    public:
        Line(QImage* image, QColor color, QWidget* parent);
        
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void updateImage(QImage* image);
    
    private:
        QImage* _image;
        QImage* _unselected_icon;
        QImage* _selected_icon;
        QColor _color;
        QWidget* _parent;
        QPoint _points[4];
        int _range;
        int _selected;
        
        void drawPoint(int x, int y, bool focus);
        void removePoint(int x, int y);
        void drawLine(int point, QColor color);
};

#endif