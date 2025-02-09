#pragma once

#include <QMainWindow>


class MainWindow : public QMainWindow 
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void onGenerateData();
    void onOpenData();
    void displayHistogram(class HistogramWidget *hw);
};