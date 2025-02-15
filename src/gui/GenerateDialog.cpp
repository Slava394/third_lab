#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "GenerateDialog.h"
#include "Generator.h"


GenerateDialog::GenerateDialog(QWidget* parent) : QDialog(parent) 
{
    setWindowTitle("Generate Data");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    QLabel* labelType = new QLabel("Generator Type:");
    comboType = new QComboBox();
    comboType->addItem("Ints");
    comboType->addItem("Points");
    comboType->addItem("Persons");
    typeLayout->addWidget(labelType);
    typeLayout->addWidget(comboType);

    QHBoxLayout* countLayout = new QHBoxLayout();
    QLabel* labelCount = new QLabel("Number of Objects:");
    lineEditCount = new QLineEdit("100000");
    countLayout->addWidget(labelCount);
    countLayout->addWidget(lineEditCount);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    QLabel* labelFile = new QLabel("File Name:");
    lineEditFile = new QLineEdit();
    fileLayout->addWidget(labelFile);
    fileLayout->addWidget(lineEditFile);

    QPushButton* btnGenerate = new QPushButton("Generate");

    layout->addLayout(typeLayout);
    layout->addLayout(countLayout);
    layout->addLayout(fileLayout);
    layout->addWidget(btnGenerate);

    connect(btnGenerate, &QPushButton::clicked, this, &GenerateDialog::onGenerateClicked);
}

void GenerateDialog::onGenerateClicked() 
{
    bool ok;
    int count = lineEditCount->text().toInt(&ok);
    if (!ok || count <= 0) 
    {
        QMessageBox::warning(this, "Error", "Invalid number of objects");
        return;
    }
    QString fileName = lineEditFile->text();
    if (fileName.isEmpty()) 
    {
        QMessageBox::warning(this, "Error", "File name is empty");
        return;
    }
    QString type = comboType->currentText();
    if (type == "Ints") 
    {
        generateInts(count, fileName.toStdString());
    } 
    else if (type == "Points") 
    {
        generatePoints(count, fileName.toStdString());
    } 
    else if (type == "Persons") 
    {
        generatePersons(count, fileName.toStdString());
    }
    QMessageBox::information(this, "Success", "Data generated successfully");
    accept();
}