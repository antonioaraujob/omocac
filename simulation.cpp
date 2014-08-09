#include "simulation.h"


// Funcion de comparacion de individuos con respecto al valor de desempeno de descubrimiento
inline static bool xLessThanF1(Individual *p1, Individual *p2)
{
    return p1->getPerformanceDiscovery() < p2->getPerformanceDiscovery();
}

// Funcion de comparacion de individuos con respecto al valor de desempeno de latencia
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

    gridSubintervalsNumber = subintervalsGrid;

    gNormative = genNormative;

    matchesPerIndividuals = matches;

    stdDeviation = stdDev;

    deployedAPs = aps;

    normativePhenotipicPart = new NormativePhenotypicPart();
}


Simulation::~Simulation()
{

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


void Simulation::initializeNormativePhenotypicPart()
{

    // obtener la lista de los individuos no dominados de la poblacion inicial
    QList<Individual *> initialNonDominatedPopulation;

    initialNonDominatedPopulation = getNonDominatedPopulationApproach1();

    // ordenarlos los no dominados con respecto a la funcion objetivo 1 de menor a mayor
    qSort(initialNonDominatedPopulation.begin(), initialNonDominatedPopulation.end(), xLessThanF1);

    // tomar los limites inferior y superior
    int lF1 = initialNonDominatedPopulation.at(0)->getPerformanceDiscovery();
    int uF1 = initialNonDominatedPopulation.at(initialNonDominatedPopulation.count()-1)->getPerformanceDiscovery();

    // ordenarlos los no dominados con respecto a la funcion objetivo 2 de menor a mayor
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

/*
    double widthF1 = (normativePhenotipicPart->getUpperF1() - normativePhenotipicPart->getLowerF1()) / gridSubintervalsNumber;
    qDebug("---ancho del intervaloF1: %f", widthF1);

    QList<GridSubInterval> intervalListF1;

    double l = normativePhenotipicPart->getLowerF1();
    double u = 0;

    qDebug("   %f",normativePhenotipicPart->getLowerF1());
    for (int i = 1; i <= 10; i++)
    {
        u = normativePhenotipicPart->getLowerF1()+widthF1*i;
        qDebug("%f - %f", l, u);
        GridSubInterval subInterval(l,u);
        intervalListF1.append(subInterval);

        qDebug("   %f",normativePhenotipicPart->getLowerF1()+widthF1*i);
        l = normativePhenotipicPart->getLowerF1()+widthF1*i;


    }

    QList<GridSubInterval> intervalListF2;


    double widthF2 = (normativePhenotipicPart->getUpperF2() - normativePhenotipicPart->getLowerF2()) / gridSubintervalsNumber;
    qDebug("---ancho del intervaloF2: %f", widthF2);

    l = normativePhenotipicPart->getLowerF2();
    u = 0;

    qDebug("   %f",normativePhenotipicPart->getLowerF2());
    for (int j = 1; j <= 10; j++)
    {
        u = normativePhenotipicPart->getLowerF2()+widthF2*j;
        qDebug("%f - %f", l, u);
        GridSubInterval subInterval(l,u);
        intervalListF2.append(subInterval);

        qDebug("   %f",normativePhenotipicPart->getLowerF2()+widthF2*j);
        l = normativePhenotipicPart->getLowerF2()+widthF2*j;
    }
*/


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
        nGrid->addIndividualToGrid(auxIndividual);

        //qDebug("===despues de agregar individuo");
        //nGrid->printGrid();
        //qDebug("===============================");
    }

}

void Simulation::printGrid()
{
    nGrid->printGrid();
}


bool Simulation::stopEvolution()
{
    if (currentGeneration == generationsMax)
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

    int i = 0;
    int j;

    while(i < p)
    {
        j = 0;

        individualI = populationList.at(i);

        while (j < p)
        {
            if (j != i)
            {
                //if ( individualDominate(Individual * xj, Individual * xi) )
                individualJ = populationList.at(j);
                if ( individualDominate(individualJ, individualI) )
                {
                    i++;
                    //continue;
                }
            }
            j++;
        }
        if (j == p)
        {
            nonDominatedPopulation.append(individualI);
        }
        i++;
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
    if ( (xj->getPerformanceDiscovery() <= xi->getPerformanceDiscovery()) &&
         (xj->getPerformanceLatency() <= xi->getPerformanceLatency()) )
    {
        conditionA = true;
    }

    // condition b
    if ( (xj->getPerformanceDiscovery() < xi->getPerformanceDiscovery()) ||
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





