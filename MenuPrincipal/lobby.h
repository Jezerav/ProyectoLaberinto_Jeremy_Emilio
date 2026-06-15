#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent = nullptr);
    ~Lobby();

private slots:
    void on_cbModo_currentTextChanged(const QString &arg1);

    void on_btnJugar_clicked();

private:
    Ui::Lobby *ui;
};

#endif // LOBBY_H
