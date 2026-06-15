#include "juego.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QKeyEvent>

Juego::Juego(QWidget *parent) : QWidget(parent) {
    filas = 0;
    columnas = 0;
    tamCelda = 80;
    mapa = nullptr;

    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(escena, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(vista);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
    this->setFocusPolicy(Qt::StrongFocus);

    // Definir un tamaño inicial cómodo para la ventana del juego
    this->resize(800, 600);
}

// Destructor para liberar la memoria del doble puntero sin fugas
Juego::~Juego() {
    liberarMapa();
}

void Juego::iniciarNivel(int nivel)
{
    nivelActual = nivel;

    liberarMapa();

    if (nivel == 1)
    {
        cargarNivel1();
    }
    else if (nivel == 2)
    {
        cargarNivel2();
    }
    else if (nivel == 3)
    {
        cargarNivel3();
    }

    dibujarMapa();
}
void Juego::cargarNivel1() {
    filas = 5;
    columnas = 5;

    // Reservar memoria dinámica para las filas y columnas (int**)
    mapa = new int*[filas];
    for (int i = 0; i < filas; i++) {
        mapa[i] = new int[columnas];
    }

    // Mapa base de prueba (1: Muro, 0: Camino, 2: Salida, 3: Jugador)
    int mapaTemporal[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 3, 0, 0, 0},
        {1, 1, 1, 0, 1},
        {1, 2, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            mapa[i][j] = mapaTemporal[i][j];

            // Guardar la posición donde inicia el prota
            if (mapa[i][j] == 3) {
                jugadorFila = i;
                jugadorColumna = j;
            }
        }
    }
}

void Juego::cargarNivel2() {
    // Por implementar más adelante
    filas = 0;
    columnas = 0;
}

void Juego::cargarNivel3() {
    // Por implementar más adelante
    filas = 0;
    columnas = 0;
}

void Juego::liberarMapa() {
    // Si la matriz tiene memoria asignada, se borra en orden inverso
    if (mapa != nullptr) {
        for (int i = 0; i < filas; i++) {
            delete[] mapa[i]; // Borra las celdas de la fila
        }
        delete[] mapa; // Borra el contenedor de filas
        mapa = nullptr;
    }
}

void Juego::dibujarMapa() {
    if (mapa == nullptr) return;

    escena->clear();

    QPixmap imgPared(":/imagenes/muro.png");
    QPixmap imgCamino(":/imagenes/camino.png");
    QPixmap imgSalida(":/imagenes/salida.png");
    QPixmap imgJugador(":/imagenes/prota.png");

    // Escalado correcto asignando cada imagen a su propia variable
    imgPared   = imgPared.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgCamino  = imgCamino.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgSalida  = imgSalida.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imgJugador = imgJugador.scaled(tamCelda, tamCelda, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {

            // Caso 1: Si es un Muro normal (1)
            if(mapa[i][j] == 1) {
                QGraphicsPixmapItem *muroItem = new QGraphicsPixmapItem(imgPared);
                muroItem->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(muroItem);
            }
            // Caso 2: Si es un Camino normal (0)
            else if(mapa[i][j] == 0) {
                QGraphicsPixmapItem *caminoItem = new QGraphicsPixmapItem(imgCamino);
                caminoItem->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(caminoItem);
            }
            // Caso 3: Si es la Salida (2) -> Camino de fondo + Salida encima
            else if(mapa[i][j] == 2) {
                // 1. Dibujamos el camino primero (atrás)
                QGraphicsPixmapItem *caminoFondo = new QGraphicsPixmapItem(imgCamino);
                caminoFondo->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(caminoFondo);

                // 2. Dibujamos la salida encima (adelante)
                QGraphicsPixmapItem *salidaItem = new QGraphicsPixmapItem(imgSalida);
                salidaItem->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(salidaItem);
            }
            // Caso 4: Si es el Jugador (3) -> Camino de fondo + Prota encima
            else if(mapa[i][j] == 3) {
                // 1. Dibujamos el camino primero (atrás)
                QGraphicsPixmapItem *caminoFondo = new QGraphicsPixmapItem(imgCamino);
                caminoFondo->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(caminoFondo);

                // 2. Se dibuja al jugador encima (adelante)
                QGraphicsPixmapItem *jugadorItem = new QGraphicsPixmapItem(imgJugador);
                jugadorItem->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(jugadorItem);
            }
            // Por si acaso hay cualquier otro valor, dejamos camino por defecto
            else {
                QGraphicsPixmapItem *caminoItem = new QGraphicsPixmapItem(imgCamino);
                caminoItem->setPos(j * tamCelda, i * tamCelda);
                escena->addItem(caminoItem);
            }

        }
    }

    // Delimitar el tamaño real que abarca la escena
    escena->setSceneRect(0, 0, columnas * tamCelda, filas * tamCelda);
}

void Juego::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    if (escena && vista) {
        // Ajusta y estira la escena para ocupar toda la pantalla manteniendo la proporción
        vista->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
    }
}

void Juego::keyPressEvent(QKeyEvent *event) {
    // Variables para calcular el posible movimiento destino
    int nuevaFila = jugadorFila;
    int nuevaColumna = jugadorColumna;

    // Detectar qué tecla presionó el usuario
    switch (event->key()) {
    case Qt::Key_W: case Qt::Key_Up:    // Arriba
        nuevaFila--;
        break;
    case Qt::Key_S: case Qt::Key_Down:  // Abajo
        nuevaFila++;
        break;
    case Qt::Key_A: case Qt::Key_Left:  // Izquierda
        nuevaColumna--;
        break;
    case Qt::Key_D: case Qt::Key_Right: // Derecha
        nuevaColumna++;
        break;
    default:
        QWidget::keyPressEvent(event); // Si es otra tecla, ignorarla
        return;
    }

    // VALIDACIÓN 1: Asegurarse de que no se salga de las dimensiones de la matriz (si no, morimos)
    if (nuevaFila >= 0 && nuevaFila < filas && nuevaColumna >= 0 && nuevaColumna < columnas) {

        // VALIDACIÓN 2: La celda destino NO es un muro (1)?
        if (mapa[nuevaFila][nuevaColumna] != 1) {

            // Si el destino es la salida (2), se puede lanzar un mensaje de victoria aquí
            if (mapa[nuevaFila][nuevaColumna] == 2) {
                // ¡Ganaste! Yyyyyy proximamente veo que mensaje
            }

            // 1. La celda vieja donde estaba el prota vuelve a ser un camino libre (0)
            mapa[jugadorFila][jugadorColumna] = 0;

            // 2. Actualizamos las coordenadas de nuestra posición actual
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;

            // 3. La nueva celda en la matriz se convierte en el jugador (3)
            mapa[jugadorFila][jugadorColumna] = 3;

            // REDIBUJAR: Borra la escena y vuelve a renderizar todo el mapa actualizado
            dibujarMapa();
        }
    }
}