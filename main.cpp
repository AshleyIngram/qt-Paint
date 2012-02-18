#include <qapplication.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "PaintWidget.h"
#include "PaintWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    //QWidget *window = new QWidget;
    //window->setGeometry(400, 300, 400, 100); //pl, pt, w, h
    
    /*QLabel *label = new QLabel("Hello World!", window, 0); //third arg - window flags?
    label->setGeometry(155, 10, 100, 30);
    
    QPushButton *quitButton = new QPushButton("Quit", window);
    quitButton->move(280, 50);
    QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    
    TextController textController(label);
    
    QPushButton *printButton = new QPushButton("Print", window);
    printButton->move(50, 50);
    QObject::connect(printButton, SIGNAL(clicked()), &textController, SLOT(Print()));*/
    PaintWindow* p = new PaintWindow();
    p->setGeometry(400, 300, 512, 512);
    p->show();
    //window->show();    
    
    return app.exec();
}
