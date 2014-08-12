#include "externalfile.h"

ExternalFile::ExternalFile(int externalFileSize)
{
    maxExternalFileSize = externalFileSize;
}

ExternalFile::~ExternalFile()
{

}





double ExternalFile::getLowerF1()
{
    return 1.0;
}


double ExternalFile::getUpperF1()
{
    return 1.0;
}


double ExternalFile::getLowerF2()
{
    return 1.0;
}



double ExternalFile::getUpperF2()
{
    return 1.0;
}


QList<Individual *> ExternalFile::getExternalFileList()
{
    return externalFileNonDominatedList;
}


void ExternalFile::addNonDominatedIndividuals(Individual * ind)
{
    // verificar las condiciones para agregar

    externalFileNonDominatedList.append(ind);
}

void ExternalFile::addNonDominatedIndividuals(QList<Individual *> nonDominatedListToInsert, NormativeGrid *nGrid)
{
    qDebug("ExternalFile::addNonDominatedIndividuals(QList<Individual *> nonDominatedListToInsert, NormativeGrid *nGrid)");

    Individual * newIndividual;

    // verificar las condiciones para agregar

    for (int i = 0; i < nonDominatedListToInsert.count(); i++)
    {
        newIndividual = nonDominatedListToInsert.at(i);

        // verificar si newIndividual ya existe en el archivo externo
        if (isIndividualInExternalFile(newIndividual))
        {
            return;
        }


        // 1) Si el individuo que se pretende agregar es dominado por algun individuo
        // del archivo externo, entonces el individuo no se debe agregar
        if ( !isNewIndividualDominatedByExternalFile(newIndividual) )
        {
            externalFileNonDominatedList.append(newIndividual);
        }
        // 2) Si newIndividual domina a algun individuo en el archivo externo, entonces
        // se introduce en su lugar, pero continua comparandose contra todos los demas.
        // Si el mismo individuo, ya agregado, dominara a algun otro, este (el dominado)
        // es eliminado del archivo externo
        else if (newIndividualDominatesAnyoneInExternalFile(newIndividual))
        {
            addNewIndividualAndCheck(newIndividual);
        }
        // 3) si newIndividual no es dominado ni domina a nadie en el archivo externo y
        // el tamano del archivo es menor que q entonces agregarlo
        else if (newIndividualNotDominatedNotDominates(newIndividual))
        {
            if (externalFileNonDominatedList.count() < maxExternalFileSize)
            {
                externalFileNonDominatedList.append(newIndividual);
            }
            else
            {
                // 4) el tamano del archivo es mayor que q entonces se busca algun individuo
                // del archivo externo cuya celda contenga mas individuos que la celda a la
                // que pertenece el individuo que se pretende agregar, y se reemplaza el
                // individuo anterior con el nuevo.
                checkGridCellAndInsertIndividual(newIndividual, nGrid);

            }
        }
    }
    Individual * ind;
    qDebug("INDIVIDUOS Del archivo externo-------");
    for (int i = 0; i < nonDominatedListToInsert.count(); i++)
    {
        ind = nonDominatedListToInsert.at(i);
        ind->printIndividual();
    }
    qDebug("-------");
}


bool ExternalFile::isNewIndividualDominatedByExternalFile(Individual * newIndividual)
{
    bool isDominated = false;

    Individual * nonDominatedindividual;

    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        nonDominatedindividual = externalFileNonDominatedList.at(i);
        if (individualDominate(nonDominatedindividual, newIndividual))
        {
            isDominated = true;
            break;
        }
    }
    return isDominated;
}

bool ExternalFile::individualDominate(Individual * xj, Individual * xi)
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


bool ExternalFile::newIndividualDominatesAnyoneInExternalFile(Individual * newIndividual)
{
    bool dominatedAnIndividual = false;

    Individual * nonDominatedindividual;

    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        nonDominatedindividual = externalFileNonDominatedList.at(i);
        if (individualDominate(newIndividual, nonDominatedindividual))
        {
            dominatedAnIndividual = true;
            break;
        }
    }
    return dominatedAnIndividual;
}

void ExternalFile::addNewIndividualAndCheck(Individual * newIndividual)
{
    qDebug("->ExternalFile::addNewIndividualAndCheck");
    Individual * nonDominatedindividual;

    bool newIndividualAlreadyInserted = false;

    // lista para mantener los indices de los individuos dominados que se deben eliminar
    QList<int> markedToRemove;

    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        nonDominatedindividual = externalFileNonDominatedList.at(i);
        if (individualDominate(newIndividual, nonDominatedindividual))
        {
            if (!newIndividualAlreadyInserted)
            {
                externalFileNonDominatedList.replace(i, newIndividual);
                newIndividualAlreadyInserted = true;
                qDebug("+ reemplazo individuo del archivo externo");
            }
            else // newIndividual ya insertado, entonces marcar nonDominatedIndividual
            {
                //externalFileNonDominatedList.removeAt(i);
                markedToRemove.append(i);
                qDebug("marcado individuo duplicado con indice %d", i);
            }
        }
    }

    // eliminar los individuos marcados del archivo externo
    for (int j = 0; j < markedToRemove.count(); j++)
    {
        externalFileNonDominatedList.removeAt(j);
    }
}


bool ExternalFile::newIndividualNotDominatedNotDominates(Individual * newIndividual)
{
    bool newIndividualNotDominated = true;
    bool newIndividualNotDominates = true;

    Individual * nonDominatedindividual;

    // verificar si newIndividual domina a alguien
    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        nonDominatedindividual = externalFileNonDominatedList.at(i);
        if (individualDominate(newIndividual, nonDominatedindividual))
        {
            newIndividualNotDominates = false;
            break;
        }
    }

    // verificar si alguien domina a newIndividual
    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        nonDominatedindividual = externalFileNonDominatedList.at(i);
        if (individualDominate(nonDominatedindividual, newIndividual))
        {
            newIndividualNotDominated = false;
            break;
        }
    }

    if ( (newIndividualNotDominates) && (newIndividualNotDominated) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


void ExternalFile::checkGridCellAndInsertIndividual(Individual * newIndividual, NormativeGrid * nGrid)
{
    // 4) el tamano del archivo es mayor que q entonces se busca algun individuo
    // del archivo externo cuya celda contenga mas individuos que la celda a la
    // que pertenece el individuo que se pretende agregar, y se reemplaza el
    // individuo anterior con el nuevo.

    int newIndividualCellCount = nGrid->getCountOfCell(newIndividual);

    Individual * externalFileindividual;

    int externalFileindividualCellCount = 0;


    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        externalFileindividual = externalFileNonDominatedList.at(i);
        externalFileindividualCellCount = nGrid->getCountOfCell(externalFileindividual);

        if (externalFileindividualCellCount > newIndividualCellCount)
        {
            // reemplazar el individuo con newIndivual
            externalFileNonDominatedList.replace(i, newIndividual);
        }
    }
}


bool ExternalFile::isIndividualInExternalFile(Individual * ind)
{
    qDebug("->ExternalFile::isIndividualInExternalFile");
    Individual * alreadyInsertedIndividual;

    for (int i = 0; i < externalFileNonDominatedList.count(); i++)
    {
        alreadyInsertedIndividual = externalFileNonDominatedList.at(i);

        // verificar si valores de F1 y F2 son iguales
        if ( (ind->getPerformanceDiscovery() == alreadyInsertedIndividual->getPerformanceDiscovery()) &&
            (ind->getPerformanceLatency() == alreadyInsertedIndividual->getPerformanceLatency()) )
        {
            qDebug("    F1 y F2 son iguales");

            bool parameterFlagDifferent = false;
            for (int j=0; j<44; j++)
            {
                if (ind->getParameter(j) != alreadyInsertedIndividual->getParameter(j))
                {
                    qDebug("    parametro %d del individuo es igual", j);
                    parameterFlagDifferent = true;
                }
                else
                {
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
}





