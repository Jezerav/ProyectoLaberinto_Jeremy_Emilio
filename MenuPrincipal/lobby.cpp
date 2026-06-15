#include "lobby.h"
#include "ui_lobby.h"
#include "../Juego/juego.h"

Lobby::Lobby(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lobby)
{
    ui->setupUi(this);

    ui->cbNivel->hide();
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_cbModo_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Libre")
    {
        ui->cbNivel->show();
    }
    else
    {
        ui->cbNivel->hide();
    }
}


void Lobby::on_btnJugar_clicked()
{
    Juego *ventanaJuego = new Juego();

    if(ui->cbModo->currentText() == "Historia")
    {
        ventanaJuego->iniciarNivel(1);
    }
    else
    {
        int nivel = ui->cbNivel->currentIndex() + 1;

        ventanaJuego->iniciarNivel(nivel);
    }

    ventanaJuego->show();
    this->hide();
}

