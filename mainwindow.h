#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "simulation.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief Clase que modela la ventana principal del programa
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:

    /**
     * @brief Objeto Simulation que abstrae todo el algoritmo cultural
     */
    Simulation * simulation;

public:

    /**
     * @brief Constructor de la clase
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Destructor de la clase
     */
    ~MainWindow();


    void populateListView();

    
public slots:

    /**
     * @brief Slot para ejecutar el algoritmo cultural al presionar un boton en
     * la interfaz grafica
     */
    void executeAlgorithm();


private:
    Ui::MainWindow *ui;
};


/** \mainpage Optimización Multiobjetivo con un algoritmo Cultural
  *
  * \section intro_sec Introducción
  *
  * En este proyecto se utiliza un algoritmo cultural para abordar un problema de optimización
  * multiobjetivo.
  *
  *
  *
  *
  */


#endif // MAINWINDOW_H
