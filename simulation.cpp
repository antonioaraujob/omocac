#include "simulation.h"


/**
 * @brief Funcion de comparacion de individuos con respecto al valor de desempeno de descubrimiento
 * @param p1 Individuo 1 a comparar
 * @param p2 Individuo 2 a comparar
 * @return Verdadero si p1 es menor que p2 con respecto a la funcion objetivo de descubrimiento
 */
inline static bool xLessThanF1(Individual *p1, Individual *p2)
{
    return p1->getPerformanceDiscovery() < p2->getPerformanceDiscovery();
}


/**
 * @brief Funcion de comparacion de individuos con respecto al valor de desempeno de latencia
 * @param p1 Individuo 1 a comparar
 * @param p2 Individuo 2 a comparar
 * @return Verdadero si p1 es menor que p2 con respecto a la funcion objetivo de latencia
 */
inline static bool xLessThanF2(Individual *p1, Individual *p2)
{
    return p1->getPerformanceLatency() < p2->getPerformanceLatency();
}

Simulation::Simulation(int population, int extFileSize, int generations, int subintervalsGrid, int genNormative,
                       int matches, int stdDev, int aps)
{
    populationSize = population;

    externalFileSize = extFileSize;

    generationsMax = generations;

    currentGeneration = 1;

    gridSubintervalsNumber = subintervalsGrid;

    gNormative = genNormative;

    matchesPerIndividuals = matches;

    stdDeviation = stdDev;

    deployedAPs = aps;

    normativePhenotipicPart = new NormativePhenotypicPart();

    externalFile = new ExternalFile(extFileSize);

    mutation = new Mutation();

    selection = new Selection();

    qDebug("Simulation:");
    qDebug("    tamano de la poblacion: %d", populationSize);
    qDebug("    numero de generaciones: %d", generationsMax);
    qDebug("    Gnormative: %d", gNormative);
    qDebug("    numero de torneos por individuo: %d", matchesPerIndividuals);
    qDebug("    desviacion estandar: %d", stdDeviation);
    qDebug("    numero de APs desplegados: %d", deployedAPs);
}


Simulation::~Simulation()
{
    delete normativePhenotipicPart;
    delete nGrid;
    delete externalFile;
    delete mutation;
}

void Simulation::initializePopulation()
{
    Individual * individuo;

    // inicializacion de la poblacion
    for (int i = 0; i < populationSize; i++)
    {
        individuo = new Individual(deployedAPs);
        individuo->printIndividual();
        populationList.append(individuo);
    }
    qDebug("tamano de la poblacion: %d",populationList.count());
    //return populationList;
}

QList<Individual *>  Simulation::getPopulationList()
{
    return populationList;
}

void Simulation::initializeNormativePhenotypicPart()
{

    // obtener la lista de los individuos no dominados de la poblacion inicial
    QList<Individual *> initialNonDominatedPopulation;

    initialNonDominatedPopulation = getNonDominatedPopulationApproach1();

    // ordenar los no dominados con respecto a la funcion objetivo 1 de menor a mayor
    qSort(initialNonDominatedPopulation.begin(), initialNonDominatedPopulation.end(), xLessThanF1);

    // tomar los limites inferior y superior
    int lF1 = initialNonDominatedPopulation.at(0)->getPerformanceDiscovery();
    int uF1 = initialNonDominatedPopulation.at(initialNonDominatedPopulation.count()-1)->getPerformanceDiscovery();

    // ordenar los no dominados con respecto a la funcion objetivo 2 de menor a mayor
    qSort(initialNonDominatedPopulation.begin(), initialNonDominatedPopulation.end(), xLessThanF2);

    int lF2 = initialNonDominatedPopulation.at(0)->getPerformanceLatency();
    int uF2 = initialNonDominatedPopulation.at(initialNonDominatedPopulation.count()-1)->getPerformanceLatency();

    // asigna los extremos de las funciones objetivo con respecto a los individuos no dominados
    normativePhenotipicPart->updateNormativePhenotypicPart(lF1, uF1, lF2, uF2);

    qDebug("| lF1: %f | uF1: %f | lF2: %f | uF2: %f |",
           normativePhenotipicPart->getLowerF1(),normativePhenotipicPart->getUpperF1(),
           normativePhenotipicPart->getLowerF2(), normativePhenotipicPart->getUpperF2());

}

void Simulation::initializeGrid()
{
    nGrid = new NormativeGrid(gridSubintervalsNumber, normativePhenotipicPart);
}


void Simulation::updateNormativePhenotypicPart()
{
    qDebug("Simulation::updateNormativePhenotypicPart");

    QList<Individual *> extFileNonDominatedPopulation;

    // obtener la lista de individuos no dominados del archivo externo
    extFileNonDominatedPopulation = externalFile->getExternalFileList();

    // ordenarlos los no dominados con respecto a la funcion objetivo 1 de menor a mayor
    qSort(extFileNonDominatedPopulation.begin(), extFileNonDominatedPopulation.end(), xLessThanF1);

    // tomar los limites inferior y superior
    int lF1 = extFileNonDominatedPopulation.at(0)->getPerformanceDiscovery();
    int uF1 = extFileNonDominatedPopulation.at(extFileNonDominatedPopulation.count()-1)->getPerformanceDiscovery();

    // ordenarlos los no dominados con respecto a la funcion objetivo 2 de menor a mayor
    qSort(extFileNonDominatedPopulation.begin(), extFileNonDominatedPopulation.end(), xLessThanF2);

    int lF2 = extFileNonDominatedPopulation.at(0)->getPerformanceLatency();
    int uF2 = extFileNonDominatedPopulation.at(extFileNonDominatedPopulation.count()-1)->getPerformanceLatency();

    // asigna los extremos de las funciones objetivo con respecto a los individuos no dominados
    normativePhenotipicPart->updateNormativePhenotypicPart(lF1, uF1, lF2, uF2);

    qDebug("nueva parte fenotipica normativa:");
    qDebug("| lF1: %f | uF1: %f | lF2: %f | uF2: %f |",
           normativePhenotipicPart->getLowerF1(),normativePhenotipicPart->getUpperF1(),
           normativePhenotipicPart->getLowerF2(), normativePhenotipicPart->getUpperF2());

    // Reconstruir la rejilla con los nuevos valores de lowerF1, upperF1, lowerF2, upperF2.
    delete nGrid;

    // Reinicializar todos los contadores de la rejilla en cero.
    nGrid = new NormativeGrid(gridSubintervalsNumber, normativePhenotipicPart);

    nGrid->printGrid();

    // Agregar todos los individuos del archivo externo al contador de su celda correspondiente.
    // De esta manera el espacio de creencias está listo de nuevo para su uso.
    updateGrid(extFileNonDominatedPopulation);

    qDebug("++++++grid despues de actualizada con los individuos del archivo externo");
    nGrid->printGrid();
    qDebug("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");



}


void Simulation::updateGrid(QList<Individual *> nonDominated)
{
/*
    Individual * ind = nonDominated.at(0);
    nGrid->addIndividualToGrid(ind);

    ind = nonDominated.at(1);
    nGrid->addIndividualToGrid(ind);
*/

    Individual * auxIndividual;
    for (int i=0; i<nonDominated.count(); i++)
    {
        auxIndividual = nonDominated.at(i);

        if(!nGrid->individualInsideGrid(auxIndividual))
        {
            qDebug("%%%%%%%% el individuo no pertenece a la grid");
            auxIndividual->printIndividual();
        }

        nGrid->addIndividualToGrid(auxIndividual);
    }

}

void Simulation::printGrid()
{
    nGrid->printGrid();
}

void Simulation::mutatePopulation()
{
    mutation->doMutation(populationList, getStdDeviation(), deployedAPs);

    mutatedPopulationList = mutation->getNewPopulation();

    mutation->printNewPopulation();
}

void Simulation::selectPopulation()
{
    selection->doSelection(mutatedPopulationList, matchesPerIndividuals, nGrid);

    populationList = selection->getSelectedPopulation();
}


void Simulation::addNonDominatedIndividualsToExternalFile(QList<Individual *> ndIndividualList)
{
    externalFile->addNonDominatedIndividuals(ndIndividualList, nGrid);
}

void Simulation::incrementGeneration()
{
    currentGeneration++;
}

int Simulation::getCurrentGenerationNumber()
{
    return currentGeneration;
}

bool Simulation::stopEvolution()
{
    if (currentGeneration > generationsMax)
        return true;
    else
        return false;
}



QList<Individual *> Simulation::getNonDominatedPopulationApproach1()
{
    qDebug("...Simulation::getNonDominatedPopulationApproach1");

    // populationList es la lista de individuos
    QList<Individual *> nonDominatedPopulation;
    int p = populationList.count();

    Individual * individualI;
    Individual * individualJ;

    for (int i=0; i<p; i++)
    {
        bool dominated = false;
        individualI = populationList.at(i);

        for (int j=0; ((j<p) && (!dominated)); j++)
        {

            if (i==j)
            {
                continue;
            }
            individualJ = populationList.at(j);
            if (individualDominate(individualJ, individualI))
            {
                dominated = true;
            }
        }
        if (!dominated)
        {
            nonDominatedPopulation.append(individualI);
        }
    }
    return nonDominatedPopulation;


}

QList<Individual *> Simulation::getNonDominatedPopulationApproach2()
{
    qDebug("...Simulation::getNonDominatedPopulationApproach2");

    int p = populationList.count();

    Individual * individualI;
    Individual * individualJ;

    // populationList es la lista de individuos
    QList<Individual *> nonDominatedPopulation;
    nonDominatedPopulation.append(populationList.at(0));

    int nonDP = nonDominatedPopulation.count();

    int i = 1;
    int j;

    while(i < p)
    {
        individualI = populationList.at(i);
        j = 0;

        while (j < nonDP)
        {
            individualJ = populationList.at(j);
            if ( individualDominate(individualI, individualJ) )
            {
                nonDominatedPopulation.removeAt(j);
            }
            else if (individualDominate(individualJ, individualI)) {
                continue;
            }
            j++;
        }
        if (j == nonDP)
        {
            nonDominatedPopulation.append(individualI);
        }
        i++;
    }

    return nonDominatedPopulation;
}


bool Simulation::individualDominate(Individual * xj, Individual * xi)
{
    //qDebug("... ... Simulation::individualDominate");

    // a solution xj is said to dominate another solution xi, and we write xj <| xi if both
    // the following conditions are true:
    //
    // condition a: Fi(xj) <= Fi(xi) to i E 1,2
    //
    // confition b: Exists j 1, 2 such that Fj(xj) < Fj(xi)

    bool conditionA = false;
    bool conditionB = false;


    // condition a
    if ( (xj->getPerformanceDiscovery() >= xi->getPerformanceDiscovery()) &&
         (xj->getPerformanceLatency() <= xi->getPerformanceLatency()) )
    {
        conditionA = true;
    }

    // condition b
    if ( (xj->getPerformanceDiscovery() > xi->getPerformanceDiscovery()) ||
         (xj->getPerformanceLatency() < xi->getPerformanceLatency()) )
    {
        conditionB = true;
    }

    if ( (conditionA) && (conditionB) )
    {
        return true;
    }else
    {
        return false;
    }
}


void Simulation::setExternalFile(ExternalFile * extFile)
{
    externalFile = extFile;
}

ExternalFile * Simulation::getExternalFile()
{
    return externalFile;
}


double Simulation::getStdDeviation()
{
    return stdDeviation;
}


void Simulation::printPopulation()
{
    for (int i = 0; i < populationList.count(); i++)
    {
        populationList.at(i)->printIndividual();
    }
}


int Simulation::getgNormative()
{
    return gNormative;
}



