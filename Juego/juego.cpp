#include "juego.h"
#include <QVBoxLayout>
#include <QBrush>
#include <QPen>

// Leyenda del mapa:
// 1 = Pared
// 0 = Camino libre
// 2 = Salida
// 3 = Posición inicial del jugador

Juego::Juego(QWidget *parent)
    : QWidget(parent),
    escena(nullptr),
    vista(nullptr),
    mapa(nullptr),
    filas(0),
    columnas(0),
    tamCelda(40)
{
    escena = new QGraphicsScene(this);
    vista  = new QGraphicsView(escena, this);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setFixedSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(vista);
    setLayout(layout);

    iniciarNivel(1);
}

// ---------------- Control de memoria dinamica -----------

void Juego::liberarMapa() {
    if(mapa != nullptr) {
        for(int i = 0; i < filas; i++) {
            delete[] mapa[i]; // liberar columnas
        }
        delete[] mapa;
        mapa = nullptr;
    }
}

// --------- Control de Nivles ---------- //

void Juego::iniciarNivel(int nivel) {
    liberarMapa();  // se libera el mapa anterior (solo si existia)
    escena->clear(); // limpia la escena

    switch(nivel) {
    case 1:
        cargarNivel1();
        break;
    case 2:
        cargarNivel2();
        break;
    case 3:
        cargarNivel3();
        break;
    default:
        cargarNivel1();
        break;
    }

    dibujarMapa();
}

// ----------- Nivel 1 ----------------

// crear el mapa dinamico
void Juego::cargarNivel1() {
    int filas = 15;
    int columans = 15;


    mapa = new int*[filas]; // primero se crea el mapa dinamico (fila)
    for(int i = 0; i < filas; i++) {
        mapa[i] = new int[columnas]; // por cada fila se crea una columna
    }

    // mapa
    int nivel1[10][10] = {
        {1,1,1,1,1},
        {1,3,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,2,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,2,1},
    };

    // poniendo el mapa en el arreglo dinamico
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            mapa[i][j] = nivel1[i][j];
        }
    }
}

void Juego::dibujarMapa() {
    escena->clear();

    QPixmap imgPared("");
    QPixmap imgCamino("");
    QPixmap imgSalida("");
    QPixmap imgJugador("");

    // Poner las imagenes del tamano de cada celda

    imgPared = imgPared.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgCamino = imgPared.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgSalida = imgPared.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgJugador = imgPared.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            QPixmap pixmapUsado;

            if(mapa[i][j] == 1) {
                pixmapUsado = imgPared;
            }
            else if(mapa[i][j] == 0) {
                pixmapUsado = imgCamino;
            }
            else if(mapa[i][j] == 2) {
                pixmapUsado = imgSalida;
            }
            else if(mapa[i][j] == 3) {
                pixmapUsado = imgJugador;
            } else {
                pixmapUsado = imgCamino;
            }

            QGraphicsPixmapItem *celda = new QGraphicsPixmapItem(pixmapUsado);
            celda->setPos(j * tamCelda, i * tamCelda);
            escena->addItem(celda);
        }
    }
    escena->setSceneRect(0, 0, columnas * tamCelda, filas * tamCelda);
    vista->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
}
