#include "PaintWidget.h"
#include "Brush.h"
#include "Line.h"
#include <qwidget.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <QResizeEvent>

const QColor WHITE("white");
const QColor BLACK("black");
const QColor RED("red");

using namespace std;

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent)
{
    this->_image = new QImage(512, 512, QImage::Format_RGB32); //size of image
    _image->fill(WHITE.rgba());
    this->_color = BLACK;
    this->_tool = new Brush(this->_image, _color);
}

PaintWidget::PaintWidget(QString filename, QWidget* parent) : QWidget(parent)
{
    this->_image = new QImage(512, 512, QImage::Format_RGB32);
    _image->load(filename);
    this->_color = BLACK;
    this->_tool = new Brush(this->_image, _color);
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
    this->_tool->mousePressEvent(event);
    this->repaint();
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    this->_tool->mouseMoveEvent(event);
    this->repaint();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    this->_tool->mouseReleaseEvent(event);
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
    this->_tool->updateImage(image);
}

void PaintWidget::save(QString filename)
{
    this->_image->save(filename);
}

void PaintWidget::setTool(string tool)
{
    if (tool == "&Brush")
    {
         delete(this->_tool);
         this->_tool = new Brush(_image, _color);
    }
    else if (tool == "&Line")
    {
        delete(this->_tool);
        this->_tool = new Line(_image, _color, this);
    }
}

PaintWidget::~PaintWidget()
{
    delete this->_image;
    delete this->_tool;
}
