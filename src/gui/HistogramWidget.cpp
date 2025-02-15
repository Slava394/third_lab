#include <QPainter>

#include "HistogramWidget.h"


HistogramWidget::HistogramWidget(QWidget* parent) : QWidget(parent) {}

void HistogramWidget::setBins(const Sequence<BinData>& binsData) 
{
    bins = binsData;
    update();
}

void HistogramWidget::paintEvent(QPaintEvent* /*event*/) 
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (bins.empty())
    {
        return;
    }
    int maxCount = 0;
    for (size_t i = 0; i < bins.getSize(); i++) 
    {
        if (bins[i].count > maxCount)
        {
            maxCount = bins[i].count;
        }
    }
    int numBins = bins.getSize();
    int spacing = 10;
    int barWidth = (width() - (numBins + 1) * spacing) / numBins;
    int x = spacing;
    for (size_t i = 0; i < bins.getSize(); i++) 
    {
        int barHeight = (maxCount > 0) ? static_cast<int>((static_cast<double>(bins[i].count) / maxCount) * (height() - 50)) : 0;
        QRect rect(x, height() - barHeight - 20, barWidth, barHeight);
        painter.setBrush(Qt::blue);
        painter.drawRect(rect);
        painter.drawText(x, height() - barHeight - 25, QString::number(bins[i].count));
        QString label = QString("[%1, %2)").arg(bins[i].lower).arg(bins[i].upper);
        painter.drawText(x, height() - 5, label);
        x += barWidth + spacing;
    }
}