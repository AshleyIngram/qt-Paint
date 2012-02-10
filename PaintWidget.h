#ifndef _PAINT_WIDGET_H
#define _PAINT_WIDGET_H 1
#include <qwidget.h>

class PaintWidget : public QWidget
{
    Q_OBJECT
    
    public:
        PaintWidget(QWidget* parent = 0);
        ~PaintWidget();
        
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void paintEvent(QPaintEvent* event);
        void resizeEvent(QResizeEvent* event);
        
    private:
        QImage* _image;
        
        void paintArea(int x, int y);
};

#endif