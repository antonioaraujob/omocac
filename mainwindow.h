#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * Clase que modela la ventana principal del programa
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    /**
     * Constructor de la clase
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destructor de la clase
     */
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
