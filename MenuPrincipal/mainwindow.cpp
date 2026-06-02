#include "mainwindow.h"
#include "manual.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSalir_clicked()
{
    this->close();
}


void MainWindow::on_btnManual_clicked()
{
    Manual *manual = new Manual();
    manual->show();
    this->hide();
}

