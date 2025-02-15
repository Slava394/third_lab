#pragma once

#include <QDialog>

#include "Sequence.h"
#include "Interval.h"
#include "HistogramWidget.h"


class QComboBox;
class QLineEdit;
class QCheckBox;
class QPushButton;

class OpenDialog : public QDialog 
{
    Q_OBJECT
public:
    OpenDialog(QWidget* parent = nullptr);
signals:
    void histogramReady(HistogramWidget *hw);
private slots:
    void onBrowse();
    void onDefineIntervals();
    void onOpen();
private:
    QComboBox* comboType;
    QLineEdit* lineEditFile;
    QCheckBox* customCheckBox;
    QPushButton* btnDefineIntervals;
    Sequence<Interval> customIntervals;
};