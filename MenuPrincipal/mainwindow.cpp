#include "mainwindow.h"
#include "manual.h"
#include "lobby.h"
#include "./ui_mainwindow.h"
#include "../Juego/juego.h"

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


void MainWindow::on_btnJugar_clicked()
{
    Lobby *lobby = new Lobby();

    lobby->show();
    this->hide();
}

