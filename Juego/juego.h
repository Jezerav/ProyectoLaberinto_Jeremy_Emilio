#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneResizeEvent>

class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

    void iniciarNivel(int nivel);
    void dibujarMapa();
    void liberarMapa();

private:
    QGraphicsScene *escena;
    QGraphicsView *vista;

    int **mapa; // aqui se utiliza el doble puntero
    int filas;
    int columnas;
    int tamCelda; // aqui esta el tamano en pixeles de cada celda

    void cargarNivel1();
    void cargarNivel2();
    void cargarNivel3();
};

#endif // JUEGO_H
