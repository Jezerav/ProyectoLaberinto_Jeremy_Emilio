#include "manual.h"
#include "mainwindow.h"
#include "ui_manual.h"

Manual::Manual(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Manual)
{
    ui->setupUi(this);
}

Manual::~Manual()
{
    delete ui;
}

void Manual::on_btnVolver_clicked()
{
    MainWindow *menu = new MainWindow();
    menu->show();

    this->close();
}

