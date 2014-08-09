#include "externalfile.h"

ExternalFile::ExternalFile()
{
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

