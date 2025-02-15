#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "MainWindow.h"
#include "GenerateDialog.h"
#include "OpenDialog.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) 
{
    setWindowTitle("Histogram Application");
    resize(800, 600);
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* actionGenerate = fileMenu->addAction("Generate Data");
    QAction* actionOpen = fileMenu->addAction("Open Data");

    connect(actionGenerate, &QAction::triggered, this, &MainWindow::onGenerateData);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::onOpenData);
}

void MainWindow::onGenerateData() 
{
    GenerateDialog dialog(this);
    dialog.exec();
}

void MainWindow::onOpenData() 
{
    OpenDialog dialog(this);
    connect(&dialog, &OpenDialog::histogramReady, this, &MainWindow::displayHistogram);
    dialog.exec();
}

void MainWindow::displayHistogram(HistogramWidget *hw) 
{
    setCentralWidget(hw);
}