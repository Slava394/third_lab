#pragma once 

#include <QWidget>

#include "Sequence.h"


class HistogramWidget : public QWidget 
{
    Q_OBJECT
public:
    struct BinData 
    {
        double lower;
        double upper;
        int count;
    };

    HistogramWidget(QWidget* parent = nullptr);
    void setBins(const Sequence<BinData>& binsData);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    Sequence<BinData> bins;
};