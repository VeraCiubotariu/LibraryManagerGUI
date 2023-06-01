#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProiectQT.h"

class ProiectQT : public QMainWindow
{
    Q_OBJECT

public:
    ProiectQT(QWidget *parent = nullptr);
    ~ProiectQT();

private:
    Ui::ProiectQTClass ui;
};
