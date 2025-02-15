#pragma once

#include <QDialog>
#include <QTableWidget>

#include "Sequence.h"
#include "Interval.h"


class IntervalsDialog : public QDialog 
{
    Q_OBJECT
public:
    IntervalsDialog(QWidget* parent = nullptr);
    const Sequence<Interval>& getIntervals() const;
private slots:
    void onAddInterval();
    void onRemoveInterval();
    void onOk();
private:
    QTableWidget* table;
    Sequence<Interval> intervals;
};