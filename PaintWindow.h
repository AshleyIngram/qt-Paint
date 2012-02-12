#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>
#include "PaintWidget.h"

class PaintWindow : public QMainWindow
{
    Q_OBJECT
    public:
        PaintWindow(QWidget* parent = 0);
        //~PaintWindow();
    
    private:
        QMenu* fileMenu;
        QAction* actionNew;
        QAction* actionSave;
        QAction* actionOpen;
        QAction* actionQuit;
        PaintWidget *paintWidget;
        
    private slots:
        void newImage();
        void openImage();
        void saveImage();
};