#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "simulation.h"


namespace Ui {
class MainWindow;
}

/**
 * Clase que modela la ventana principal del programa
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    Simulation * simulation;

public:

    /**
     * Constructor de la clase
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destructor de la clase
     */
    ~MainWindow();


    void populateListView();

    
public slots:
    void executeAlgorithm();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
