#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

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

#define DEFAULT_BIN_COUNT 15


OpenDialog::OpenDialog(QWidget* parent) : QDialog(parent) 
{
    setWindowTitle("Open Data and Build Histogram");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    QLabel* labelType = new QLabel("Object Type:");
    comboType = new QComboBox();
    comboType->addItem("Ints");
    comboType->addItem("Points (x)");
    comboType->addItem("Points (y)");
    comboType->addItem("Persons (age)");
    comboType->addItem("Persons (salary)");
    typeLayout->addWidget(labelType);
    typeLayout->addWidget(comboType);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    QLabel* labelFile = new QLabel("File:");
    lineEditFile = new QLineEdit();
    QPushButton* btnBrowse = new QPushButton("Browse");
    fileLayout->addWidget(labelFile);
    fileLayout->addWidget(lineEditFile);
    fileLayout->addWidget(btnBrowse);

    QHBoxLayout* customLayout = new QHBoxLayout();
    customCheckBox = new QCheckBox("Use custom intervals");
    btnDefineIntervals = new QPushButton("Define Intervals");
    btnDefineIntervals->setEnabled(false);
    customLayout->addWidget(customCheckBox);
    customLayout->addWidget(btnDefineIntervals);

    QPushButton* btnOpen = new QPushButton("Open and Build Histogram");

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
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        int temp;
        bool first = true;
        int minVal = 0, maxVal = 0;
        while (in >> temp) 
        {
            if (first) 
            {
                minVal = temp;
                maxVal = temp;
                first = false;
            } 
            else 
            {
                if (temp < minVal) 
                {
                    minVal = temp;
                }
                if (temp > maxVal) 
                {
                    maxVal = temp;
                }
            }
        }
        in.clear();
        in.seekg(0);
        int numBins = DEFAULT_BIN_COUNT;
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
        Histogram<int> hist([](const int &i) -> double { return static_cast<double>(i); }, intervalsVec);
        while (in >> temp) 
        {
            hist.updateData(temp);
        }
        in.close();
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const auto &bin) 
        {
            HistogramWidget::BinData data;
            data.lower = interval.getLower();
            data.upper = interval.getUpper();
            data.count = bin.getCount();
            binsData.append(data);
        });
        HistogramWidget* hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Points (x)") 
    {
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        double x, y;
        bool first = true;
        double minX = 0, maxX = 0;
        while (in >> x >> y) 
        {
            if (first) 
            {
                minX = x;
                maxX = x;
                first = false;
            } 
            else 
            {
                if (x < minX) 
                {
                    minX = x;
                }
                if (x > maxX) 
                {
                    maxX = x;
                }
            }
        }
        in.clear();
        in.seekg(0);
        int numBins = DEFAULT_BIN_COUNT;
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
        Histogram<Point> hist([](const Point &p) -> double { return p.x; }, intervalsVec);
        while (in >> x >> y) 
        {
            Point p(x, y);
            hist.updateData(p);
        }
        in.close();
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const auto &bin) 
        {
            HistogramWidget::BinData data;
            data.lower = interval.getLower();
            data.upper = interval.getUpper();
            data.count = bin.getCount();
            binsData.append(data);
        });
        HistogramWidget* hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Points (y)") 
    {
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        double x, y;
        bool first = true;
        double minY = 0, maxY = 0;
        while (in >> x >> y) 
        {
            if (first) 
            {
                minY = y;
                maxY = y;
                first = false;
            } 
            else 
            {
                if (y < minY) 
                {
                    minY = y;
                }
                if (y > maxY) 
                {
                    maxY = y;
                }
            }
        }
        in.clear();
        in.seekg(0);
        int numBins = DEFAULT_BIN_COUNT;
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
        Histogram<Point> hist([](const Point &p) -> double { return p.y; }, intervalsVec);
        while (in >> x >> y) 
        {
            Point p(x, y);
            hist.updateData(p);
        }
        in.close();
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const auto &bin) 
        {
            HistogramWidget::BinData data;
            data.lower = interval.getLower();
            data.upper = interval.getUpper();
            data.count = bin.getCount();
            binsData.append(data);
        });
        HistogramWidget* hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Persons (age)") 
    {
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        std::string name;
        int age;
        double salary;
        bool first = true;
        int minAge = 0, maxAge = 0;
        while (in >> name >> age >> salary) 
        {
            if (first) 
            {
                minAge = age;
                maxAge = age;
                first = false;
            } 
            else 
            {
                if (age < minAge) 
                {
                    minAge = age;
                }
                if (age > maxAge) 
                {
                    maxAge = age;
                }
            }
        }
        in.clear();
        in.seekg(0);
        int numBins = DEFAULT_BIN_COUNT;
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
        Histogram<Person> hist([](const Person &p) -> double { return static_cast<double>(p.age); }, intervalsVec);
        while (in >> name >> age >> salary) 
        {
            Person p(name, age, salary);
            hist.updateData(p);
        }
        in.close();
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const auto &bin) 
        {
            HistogramWidget::BinData data;
            data.lower = interval.getLower();
            data.upper = interval.getUpper();
            data.count = bin.getCount();
            binsData.append(data);
        });
        HistogramWidget* hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
    else if (type == "Persons (salary)") 
    {
        std::ifstream in(fileName.toStdString());
        if (!in) 
        {
            QMessageBox::warning(this, "Error", "Cannot open file");
            return;
        }
        std::string name;
        int age;
        double salary;
        bool first = true;
        double minSalary = 0, maxSalary = 0;
        while (in >> name >> age >> salary) 
        {
            if (first) 
            {
                minSalary = salary;
                maxSalary = salary;
                first = false;
            } 
            else 
            {
                if (salary < minSalary) 
                {
                    minSalary = salary;
                }
                if (salary > maxSalary) 
                {
                    maxSalary = salary;
                }
            }
        }
        in.clear();
        in.seekg(0);
        int numBins = DEFAULT_BIN_COUNT;
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
        Histogram<Person> hist([](const Person &p) -> double { return p.salary; }, intervalsVec);
        while (in >> name >> age >> salary) 
        {
            Person p(name, age, salary);
            hist.updateData(p);
        }
        in.close();
        Sequence<HistogramWidget::BinData> binsData;
        hist.getBins().inorder([&](const Interval &interval, const auto &bin) 
        {
            HistogramWidget::BinData data;
            data.lower = interval.getLower();
            data.upper = interval.getUpper();
            data.count = bin.getCount();
            binsData.append(data);
        });
        HistogramWidget* hw = new HistogramWidget();
        hw->setBins(binsData);
        emit histogramReady(hw);
        accept();
    }
}