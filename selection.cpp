#include "selection.h"



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



Selection::Selection()
{
    selectedPopulation.clear();
    tournamentsWinners.clear();
}

Selection::~Selection()
{
}

QList<Individual *> Selection::getSelectedPopulation()
{
    return selectedPopulation;
}

void Selection::doSelection(QList<Individual *> population2p, int matches, NormativeGrid *nGrid)
{
    //selectedPopulation.clear();

    // lista de adversarios de tamano matches
    QList<Individual *> adversaryList;

    int randomIndex = 0;

    Individual * selectedIndividual;
    Individual * adversary;

    int i = 0;
    //for (int i=0; i<population2p; i++)
    while( i < population2p.count())
    {
        // seleccionar individuo
        selectedIndividual = population2p.at(i);

        // escoger matches individuos aletorios y agregarlos a la lista de adversarios
        while( adversaryList.count() < matches)
        {
            // obtener un indice aleatorio de un individuo dentro de population2p
            randomIndex = getRandom(population2p.count()-1);

            // se selecciono el indice del mismo inviduo por lo tanto se escoge otro
            if (randomIndex == i)
            {
                continue;
            }
            adversary = population2p.at(randomIndex);
            adversaryList.append(adversary);
        }
        // ejecutar los torneos del individuo contra los adversarios
        makeTournaments(i, selectedIndividual, adversaryList, nGrid);

        // incrementar el valor de i
        i++;
        adversaryList.clear();

    } // fin de los torneos


    // agregar los P individuos con mayores valores de victorias a la lista de la poblacion
    // seleccionada selectedPopulation
    //

    // contenedor auxiliar para realizar la seleccion de los P individuos con mas victorias
    QMultiMap<int, int> auxiliaryMap;

    QMapIterator<int, int> iterator1(tournamentsWinners);

    while (iterator1.hasNext())
    {
        iterator1.next();
        auxiliaryMap.insert(iterator1.value(), iterator1.key()); //swap value and key
    }

    // ----------------------------
    // impresion de prueba
    /*
    QMap<int, int>::iterator it = tournamentsWinners.begin();
    while (it != tournamentsWinners.end())
    {
        qDebug(" index %d value %d", it.key(), it.value() );
        ++it;
    }
    */
    // ----------------------------

    // ----------------------------
    // impresion de prueba
    /*
    QMap<int, int>::iterator it3 = auxiliaryMap.begin();
    while (it3 != auxiliaryMap.end()) {
        qDebug(" value %d index %d", it3.key(), it3.value() );
        ++it3;
    }
    */
    // ----------------------------

    QList<int> indexToInsertInPopulation = auxiliaryMap.values();
    for (int k=indexToInsertInPopulation.count()-1; k > (indexToInsertInPopulation.count()/2)-1; k--)
    {
        //qDebug("indice %d", indexToInsertInPopulation.at(k));
        selectedPopulation.append(population2p.at(k));
    }
    // evaluar cada individuo de la poblacion seleccionada o hacer fuera en la clase Simulation
    // TODO

    qDebug("TAMANO DE LA POBLACION SELECCIONADA DESPUES DE LOS TORNEOS: %d", selectedPopulation.count());
}


void Selection::makeTournaments(int individualIndex, Individual * individual, QList<Individual *> adversaryList, NormativeGrid * nGrid)
{
    // contador de las victorias de individual
    int victoriesCount = 0;

    Individual * adversary;

    for (int i=0; i<adversaryList.count(); i++)
    {
        adversary = adversaryList.at(i);

        // verificar condiciones:
        //
        // 1) si individual domina a otro gana el individuo no dominado
        if (individualDominate(individual, adversary))
        {
            victoriesCount++;
        }
        else //
        {
            // 2) si no son comparables, o sus valores de funciones objetivo son iguales
            if ( (individual->getPerformanceDiscovery() == adversary->getPerformanceDiscovery()) &&
                ((individual->getPerformanceLatency() == adversary->getPerformanceLatency())) )
            {
                // a) si ambos estan dentro de la rejilla del espacio de creencias, gana el que se encuentre en una
                // celda menos poblada (segun el contador de las celdas)
                if ( (nGrid->individualInsideGrid(individual)) && (nGrid->individualInsideGrid(adversary)) )
                {
                    int counterIndividual = 0;
                    int counterAdversary = 0;

                    // ver los contadores de las posiciones
                    counterIndividual = nGrid->getCountOfCell(individual);
                    counterAdversary = nGrid->getCountOfCell(adversary);

                    if (counterIndividual < counterAdversary)
                    {
                        // individual gana porque se encuentra en una celda menos poblada
                        victoriesCount++;
                    }
                }

                // b) si alguno cae fuera de la rejilla, gana el que este afuera
                if ( !nGrid->individualInsideGrid(individual) )
                {
                    qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    qDebug("individuo cayo fuera de la rejilla");
                    individual->printIndividual();
                    qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    victoriesCount++;
                }
            }
        }

    } // fin del for de recorrido de la lista de adversarios


    //qDebug("individualIndex %d", individualIndex);
    //qDebug("victoriesCount %d", victoriesCount);
    tournamentsWinners.insert(individualIndex, victoriesCount);
}

bool Selection::individualDominate(Individual * xj, Individual * xi)
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


int Selection::getRandom(int high)
{
    int low = 1;
    //int high = 11;
    return qrand() % ((high + 1) - low) + low;
}