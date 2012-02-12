#include "PaintWindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>

PaintWindow::PaintWindow(QWidget* parent) : QMainWindow(parent)
{
    actionNew = new QAction(tr("&New Image"), this);
    actionNew->setShortcut(QKeySequence::New);
    actionNew->setStatusTip(tr("New Plain White Image"));
    connect(actionNew, SIGNAL(triggered()), this, SLOT(newImage()));
    
    actionOpen = new QAction(tr("&Load Image"), this);
    actionOpen->setShortcut(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open an Image"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    
    actionSave = new QAction(tr("&Save Image"), this);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save your Image"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveImage()));
    
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(QKeySequence::Quit);
    actionQuit->setStatusTip(tr("Quit the Application"));
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionQuit);
}

void PaintWindow::newImage()
{
    delete(this->paintWidget);
    this->paintWidget  = new PaintWidget(this);
    this->setCentralWidget(paintWidget);
}

void PaintWindow::openImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "./", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!filename.isNull())
    {
        delete(this->paintWidget);
        this->paintWidget = new PaintWidget(filename, this);
        this->setCentralWidget(paintWidget);
    }
}

void PaintWindow::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image (*.png *.jpg *.bmp)"));
    this->paintWidget->save(filename);
}