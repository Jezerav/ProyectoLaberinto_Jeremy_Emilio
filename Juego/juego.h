#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QShowEvent>
#include <QKeyEvent>

class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

    void iniciarNivel(int nivel);
    void dibujarMapa();
    void liberarMapa();

protected:
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *escena;
    QGraphicsView *vista;

    int **mapa;
    int filas;
    int columnas;
    int tamCelda;
    int jugadorFila;
    int jugadorColumna;

    void cargarNivel1();
    void cargarNivel2();
    void cargarNivel3();
};

#endif // JUEGO_H