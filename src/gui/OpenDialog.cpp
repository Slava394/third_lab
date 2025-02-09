#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>

#include <fstream>
#include <string>

#include "OpenDialog.h"
#include "IntervalsDialog.h"
#include "Sequence.h"
#include "Generator.h"
#include "Point.h"
#include "Person.h"
#include "Histogram.h"
#include "Interval.h"


OpenDialog::OpenDialog(QWidget *parent) : QDialog(parent) 
{
    setWindowTitle("Open Data and Build Histogram");
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *typeLayout = new QHBoxLayout();
    QLabel *labelType = new QLabel("Object Type:");
    comboType = new QComboBox();
    comboType->addItem("Ints");
    comboType->addItem("Points (x)");
    comboType->addItem("Points (y)");
    comboType->addItem("Persons (age)");
    comboType->addItem("Persons (salary)");
    typeLayout->addWidget(labelType);
    typeLayout->addWidget(comboType);

    QHBoxLayout *fileLayout = new QHBoxLayout();
    QLabel *labelFile = new QLabel("File:");
    lineEditFile = new QLineEdit();
    QPushButton *btnBrowse = new QPushButton("Browse");
    fileLayout->addWidget(labelFile);
    fileLayout->addWidget(lineEditFile);
    fileLayout->addWidget(btnBrowse);

    QHBoxLayout *customLayout = new QHBoxLayout();
    customCheckBox = new QCheckBox("Use custom intervals");
    btnDefineIntervals = new QPushButton("Define Intervals");
    btnDefineIntervals->setEnabled(false);
    customLayout->addWidget(customCheckBox);
    customLayout->addWidget(btnDefineIntervals);

    QPushButton *btnOpen = new QPushButton("Open and Build Histogram");

    layout->addLayout(typeLayout);
    layout->addLayout(fileLayout);
    layout->addLayout(customLayout);
    layout->addWidget(btnOpen);

    connect(btnBrowse, &QPushButton::clicked, this, &OpenDialog::onBrowse);
    connect(btnOpen, &QPushButton::clicked, this, &OpenDialog::onOpen);
    connect(customCheckBox, &QCheckBox::toggled, btnDefineIntervals, &QPushButton::setEnabled);
    connect(btnDefineIntervals, &QPushButton::clicked, this, &OpenDialog::onDefineIntervals);
}

void OpenDialog::onBrowse() 
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Data File");
    if (!fileName.isEmpty()) 
    {
        lineEditFile->setText(fileName);
    }
}

void OpenDialog::onDefineIntervals() 
{
    IntervalsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) 
    {
        customIntervals = dialog.getIntervals();
    }
}

void OpenDialog::onOpen() 
{
    QString type = comboType->currentText();
    QString fileName = lineEditFile->text();
    if (fileName.isEmpty()) 
    {
        QMessageBox::warning(this, "Error", "No file selected");
        return;
    }
    bool useCustom = customCheckBox->isChecked() && !customIntervals.empty();

    if (type == "Ints") 
    {
        Sequence<int> ints;
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        int value;
        while (in >> value) 
        {
            ints.append(value);
        }
        in.close();
        if (ints.getSize() == 0) 
        {
            QMessageBox::warning(this, "Error", "No data found");
            return;
        }
        int minVal = ints[0], maxVal = ints[0];
        for (size_t i = 0; i < ints.getSize(); i++) 
        {
            if (ints[i] < minVal) minVal = ints[i];
            if (ints[i] > maxVal) maxVal = ints[i];
        }
        int numBins = 10;
        double binWidth = (maxVal == minVal) ? 1.0 : (maxVal - minVal) / static_cast<double>(numBins);
        Sequence<Interval> intervalsVec;
        if (!useCustom) 
        {
            for (int i = 0; i < numBins; i++) 
            {
                intervalsVec.append(Interval(minVal + i * binWidth, minVal + (i + 1) * binWidth));
            }
        } 
        else 
        {
            intervalsVec = customIntervals;
        }
        Histogram<int> hist(ints, [](const int &i) -> double {
            return static_cast<double>(i);
        }, intervalsVec);
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const HistogramBin &bin) {
            HistogramWidget::BinData data;
            data.lower = interval.lower;
            data.upper = interval.upper;
            data.count = bin.count;
            binsData.append(data);
        });
        HistogramWidget *hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Points (x)") 
    {
        Sequence<Point> points;
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        double x, y;
        while (in >> x >> y) 
        {
            points.append(Point(x, y));
        }
        in.close();
        if (points.getSize() == 0) 
        {
            QMessageBox::warning(this, "Error", "No data found");
            return;
        }
        double minX = points[0].x, maxX = points[0].x;
        for (size_t i = 0; i < points.getSize(); i++) 
        {
            if (points[i].x < minX) minX = points[i].x;
            if (points[i].x > maxX) maxX = points[i].x;
        }
        int numBins = 10;
        double binWidth = (maxX - minX) / numBins;
        Sequence<Interval> intervalsVec;
        if (!useCustom) 
        {
            for (int i = 0; i < numBins; i++) 
            {
                intervalsVec.append(Interval(minX + i * binWidth, minX + (i + 1) * binWidth));
            }
        } 
        else 
        {
            intervalsVec = customIntervals;
        }
        Histogram<Point> hist(points, [](const Point &p) -> double {
            return p.x;
        }, intervalsVec);
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const HistogramBin &bin) {
            HistogramWidget::BinData data;
            data.lower = interval.lower;
            data.upper = interval.upper;
            data.count = bin.count;
            binsData.append(data);
        });
        HistogramWidget *hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Points (y)") 
    {
        Sequence<Point> points;
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        double x, y;
        while (in >> x >> y) 
        {
            points.append(Point(x, y));
        }
        in.close();
        if (points.getSize() == 0) 
        {
            QMessageBox::warning(this, "Error", "No data found");
            return;
        }
        double minY = points[0].y, maxY = points[0].y;
        for (size_t i = 0; i < points.getSize(); i++) 
        {
            if (points[i].y < minY) minY = points[i].y;
            if (points[i].y > maxY) maxY = points[i].y;
        }
        int numBins = 10;
        double binWidth = (maxY - minY) / numBins;
        Sequence<Interval> intervalsVec;
        if (!useCustom) 
        {
            for (int i = 0; i < numBins; i++) 
            {
                intervalsVec.append(Interval(minY + i * binWidth, minY + (i + 1) * binWidth));
            }
        } 
        else 
        {
            intervalsVec = customIntervals;
        }
        Histogram<Point> hist(points, [](const Point &p) -> double {
            return p.y;
        }, intervalsVec);
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const HistogramBin &bin) {
            HistogramWidget::BinData data;
            data.lower = interval.lower;
            data.upper = interval.upper;
            data.count = bin.count;
            binsData.append(data);
        });
        HistogramWidget *hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Persons (age)") 
    {
        Sequence<Person> persons;
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        std::string name;
        int age;
        double salary;
        while (in >> name >> age >> salary) 
        {
            persons.append(Person(name, age, salary));
        }
        in.close();
        if (persons.getSize() == 0) 
        {
            QMessageBox::warning(this, "Error", "No data found");
            return;
        }
        int numBins = 10;
        int minAge = persons[0].age, maxAge = persons[0].age;
        for (size_t i = 0; i < persons.getSize(); i++) 
        {
            if (persons[i].age < minAge) minAge = persons[i].age;
            if (persons[i].age > maxAge) maxAge = persons[i].age;
        }
        double binWidth = (maxAge - minAge) / static_cast<double>(numBins);
        Sequence<Interval> intervalsVec;
        if (!useCustom) 
        {
            for (int i = 0; i < numBins; i++) 
            {
                intervalsVec.append(Interval(minAge + i * binWidth, minAge + (i + 1) * binWidth));
            }
        } 
        else 
        {
            intervalsVec = customIntervals;
        }
        Histogram<Person> hist(persons, [](const Person &p) -> double {
            return p.age;
        }, intervalsVec);
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const HistogramBin &bin) {
            HistogramWidget::BinData data;
            data.lower = interval.lower;
            data.upper = interval.upper;
            data.count = bin.count;
            binsData.append(data);
        });
        HistogramWidget *hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Persons (salary)") 
    {
        Sequence<Person> persons;
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        std::string name;
        int age;
        double salary;
        while (in >> name >> age >> salary) 
        {
            persons.append(Person(name, age, salary));
        }
        in.close();
        if (persons.getSize() == 0) 
        {
            QMessageBox::warning(this, "Error", "No data found");
            return;
        }
        int numBins = 10;
        double minSalary = persons[0].salary, maxSalary = persons[0].salary;
        for (size_t i = 0; i < persons.getSize(); i++) 
        {
            if (persons[i].salary < minSalary) minSalary = persons[i].salary;
            if (persons[i].salary > maxSalary) maxSalary = persons[i].salary;
        }
        double binWidth = (maxSalary - minSalary) / static_cast<double>(numBins);
        Sequence<Interval> intervalsVec;
        if (!useCustom) 
        {
            for (int i = 0; i < numBins; i++) 
            {
                intervalsVec.append(Interval(minSalary + i * binWidth, minSalary + (i + 1) * binWidth));
            }
        } 
        else 
        {
            intervalsVec = customIntervals;
        }
        Histogram<Person> hist(persons, [](const Person &p) -> double {
            return p.salary;
        }, intervalsVec);
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const HistogramBin &bin) {
            HistogramWidget::BinData data;
            data.lower = interval.lower;
            data.upper = interval.upper;
            data.count = bin.count;
            binsData.append(data);
        });
        HistogramWidget *hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
}