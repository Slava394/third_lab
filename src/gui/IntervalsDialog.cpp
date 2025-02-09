#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>

#include "IntervalsDialog.h"


IntervalsDialog::IntervalsDialog(QWidget *parent) : QDialog(parent) 
{
    setWindowTitle("Define Intervals");
    QVBoxLayout *layout = new QVBoxLayout(this);

    table = new QTableWidget(0, 2, this);
    table->setHorizontalHeaderLabels(QStringList() << "Lower" << "Upper");
    table->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(table);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnAdd = new QPushButton("Add Interval");
    QPushButton *btnRemove = new QPushButton("Remove Selected");
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnRemove);
    layout->addLayout(btnLayout);

    QHBoxLayout *okCancelLayout = new QHBoxLayout();
    QPushButton *btnOk = new QPushButton("OK");
    QPushButton *btnCancel = new QPushButton("Cancel");
    okCancelLayout->addWidget(btnOk);
    okCancelLayout->addWidget(btnCancel);
    layout->addLayout(okCancelLayout);

    connect(btnAdd, &QPushButton::clicked, this, &IntervalsDialog::onAddInterval);
    connect(btnRemove, &QPushButton::clicked, this, &IntervalsDialog::onRemoveInterval);
    connect(btnOk, &QPushButton::clicked, this, &IntervalsDialog::onOk);
    connect(btnCancel, &QPushButton::clicked, this, &IntervalsDialog::reject);
}

const Sequence<Interval>& IntervalsDialog::getIntervals() const 
{
    return intervals;
}

void IntervalsDialog::onAddInterval() 
{
    int row = table->rowCount();
    table->insertRow(row);
    QTableWidgetItem *itemLower = new QTableWidgetItem("0");
    QTableWidgetItem *itemUpper = new QTableWidgetItem("1");
    table->setItem(row, 0, itemLower);
    table->setItem(row, 1, itemUpper);
}

void IntervalsDialog::onRemoveInterval() 
{
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    if (!selectedItems.isEmpty()) 
    {
        int row = selectedItems.first()->row();
        table->removeRow(row);
    }
}

void IntervalsDialog::onOk() 
{
    intervals.clear();
    for (int row = 0; row < table->rowCount(); ++row) 
    {
        bool ok1, ok2;
        double lower = table->item(row, 0)->text().toDouble(&ok1);
        double upper = table->item(row, 1)->text().toDouble(&ok2);
        if (!ok1 || !ok2) 
        {
            QMessageBox::warning(this, "Error", "Invalid interval values");
            return;
        }
        if (lower >= upper) 
        {
            QMessageBox::warning(this, "Error", "Lower bound must be less than upper bound");
            return;
        }
        intervals.append(Interval(lower, upper));
    }
    accept();
}