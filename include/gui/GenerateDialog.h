#pragma once

#include <QDialog>


class QComboBox;
class QLineEdit;

class GenerateDialog : public QDialog 
{
    Q_OBJECT
public:
    GenerateDialog(QWidget* parent = nullptr);
private slots:
    void onGenerateClicked();
private:
    QComboBox* comboType;
    QLineEdit* lineEditCount;
    QLineEdit* lineEditFile;
};