#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "individual.h"
#include "simulation.h"

#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>
#include <QSet>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(600, 577);

    // Validadores para los parametros del algoritmo
    QValidator * validatorPopSize = new QIntValidator(1, 1000, this);
    ui->lineEditPopulationSize->setValidator(validatorPopSize);
    ui->lineEditPopulationSize->setToolTip("[1..1000]");

    QValidator * validatorGenerations = new QIntValidator(1, 50, this);
    ui->lineEditGenerationNumber->setValidator(validatorGenerations);
    ui->lineEditGenerationNumber->setToolTip("[1..50]");

    QValidator * validatorAcceptedPercentage = new QIntValidator(1, 100, this);
    ui->lineEditAceptationPercentage->setValidator(validatorAcceptedPercentage);
    ui->lineEditAceptationPercentage->setToolTip("[1..100]");

    QValidator * validatorMutationStd = new QIntValidator(1, 10, this);
    ui->lineEditMutationStd->setValidator(validatorMutationStd);
    ui->lineEditMutationStd->setToolTip("[1..10]");

    QValidator * validatorExternalFileSize = new QIntValidator(1, 100, this);
    ui->lineEditExternalFileSize->setValidator(validatorExternalFileSize);
    ui->lineEditExternalFileSize->setToolTip("[1..100]");

    QValidator * validatorGridSubintervals = new QIntValidator(1, 10, this);
    ui->lineEditGridSubintervals->setValidator(validatorGridSubintervals);
    ui->lineEditGridSubintervals->setToolTip("[1..10]");

    QValidator * validatorGnormative = new QIntValidator(1, 20, this);
    ui->lineEditGnormative->setValidator(validatorGnormative);
    ui->lineEditGnormative->setToolTip("[1..20]");

    int matches = ui->lineEditPopulationSize->text().toInt()/2;
    QValidator * validatorMatchesPerTournament= new QIntValidator(1, matches, this);
    ui->lineEditMatchPerTournament->setValidator(validatorMatchesPerTournament);
    ui->lineEditMatchPerTournament->setText(QString::number(matches));
    ui->lineEditMatchPerTournament->setToolTip("Un valor recomendado es Poblacion/2");

    QValidator * validatorApsNumber= new QIntValidator(1, 100, this);
    ui->lineEditApsNumber->setValidator(validatorApsNumber);
    ui->lineEditApsNumber->setToolTip("[1..100]");


    //qsrand((uint)QTime::currentTime().msec());


    // creacion del objeto simulacion
    Simulation * simulation = new Simulation(ui->lineEditPopulationSize->text().toInt(),
                                             ui->lineEditExternalFileSize->text().toInt(),
                                             ui->lineEditGenerationNumber->text().toInt(),
                                             ui->lineEditGridSubintervals->text().toInt(),
                                             ui->lineEditGnormative->text().toInt(),
                                             matches,
                                             ui->lineEditMutationStd->text().toInt(),
                                             ui->lineEditApsNumber->text().toInt());

    simulation->initializePopulation();


    QList<Individual *> nonDominatedList = simulation->getNonDominatedPopulationApproach1();
    qDebug("Numero de individuos en la poblacion no dominada:");
    qDebug(qPrintable(QString::number(nonDominatedList.count())));
    for (int i = 0; i < nonDominatedList.count(); i++)
    {
        nonDominatedList.at(i)->printIndividual();
    }

    simulation->initializeNormativePhenotypicPart();
    qDebug("...se acaba de inicializar la parte normativa fenotipica del espacio de creencias");

    simulation->initializeGrid();
    qDebug("...se acaba de inicializar la grid");


    simulation->updateGrid(nonDominatedList);
    qDebug("...se acaba de agregar un individuo a la grid");

    simulation->printGrid();
    qDebug("Numero de individuos en la poblacion no dominada:");
    qDebug(qPrintable(QString::number(nonDominatedList.count())));

}

MainWindow::~MainWindow()
{
    delete ui;
}



/*
    // secuencia de scanning aleatoria
    int marcados = 0;

    int low = 1;
    int high = 11;
    int value = 0;

    QSet<int> set;
    QString seq;

    while(marcados < 11)
    {
        value = qrand() % ((high + 1) - low) + low;
        if (!set.contains(value))
        {
            set.insert(value);
            marcados++;
            seq.append(QString::number(value));
            seq.append(",");
        }
    }
    qDebug("secuencia de scanning:");
    qDebug(qPrintable(seq));
*/
