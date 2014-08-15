#include "individual.h"

#include "simulation.h"

#include <QTime>

Individual::Individual(int numberOfApsDeployed)
{
    //qsrand((uint)QTime::currentTime().msec());

    // asignar el valor unico del identificador del individuo
    individualId = Simulation::getNewindividualId();

    // se deben crear los 33 parametros
    // C1,Min1,Max1,AP1,C2,Min2,Max2,AP2,...,C11,Min11,Max11,AP11

    int randomChannel = 0;
    for (int i=0; i<11; i++)
    {
        randomChannel = getRandomChannel();
        parametersList.append(randomChannel);

        parametersList.append(getRandomMinChannelTime());
        parametersList.append(getRandomMaxChannelTime());

        parametersList.append(getAPNumberOnChannel(numberOfApsDeployed, randomChannel));

        wonMatchesCounter = 0;
    }

    // calcular el valor de desempeno para el individuo
    calculatePerformanceValue();

    // calcular el valor de desempeno para la descubierta
    setPerformanceDiscovery(getRandomMaxChannelTime());

    // calcular el valor de desempeno para la latencia
    setPerformanceLatency(getRandomMaxChannelTime());

}


Individual::Individual(Individual &p)
{
    for (int i=0; i<44; i++)
    {
        parametersList.append(p.getParameter(i));
    }

    // calcular el valor de desempeno para el individuo
    calculatePerformanceValue();

    // calcular el valor de desempeno para la descubierta
    setPerformanceDiscovery(getRandomMaxChannelTime());

    // calcular el valor de desempeno para la latencia
    setPerformanceLatency(getRandomMaxChannelTime());
}

int Individual::getIndividualId()
{
    return individualId;
}


int Individual::getRandomChannel()
{
/*
    // el rango es 1 <= channel <= 11
    int low = 1;
    int high = 11;
    return qrand() % ((high + 1) - low) + low;
*/

    int low = 1;
    int high = 11;
    int value = 0;

    while(true)
    {
        value = qrand() % ((high + 1) - low) + low;
        if (!channelSequenceSet.contains(value))
        {
            channelSequenceSet.insert(value);
            //qDebug("canal seleccionado: %d", value);
            return value;
        }
    }
}


double Individual::getRandomMinChannelTime()
{
    // el rango es 0 <= MinChannelTime <= 10 en ms
    int low = 0;
    int high = 10;
    return qrand() % ((high + 1) - low) + low;
}

double Individual::getRandomMaxChannelTime(){

    // el rango es 10 <= MaxChannelTime <= 100
    int low = 10;
    int high = 100;
    return qrand() % ((high + 1) - low) + low;
}

double Individual::getAPNumberOnChannel(int numberOfApsDeployed, int channel){

    // la proporcion de APs que operan en cada canal es tomada del articulo
    //
    if (channel == 1)
    {
        return (numberOfApsDeployed * 18)/100;
    }
    if (channel == 2)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 3)
    {
        return (numberOfApsDeployed * 3)/100;
    }
    if (channel == 4)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 5)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 6)
    {
        return (numberOfApsDeployed * 36)/100;
    }
    if (channel == 7)
    {
        return (numberOfApsDeployed * 2)/100;
    }
    if (channel == 8)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 9)
    {
        return (numberOfApsDeployed * 6)/100;
    }
    if (channel == 10)
    {
        return (numberOfApsDeployed * 6)/100;
    }
    if (channel == 11)
    {
        return (numberOfApsDeployed * 25)/100;
    }
}

void Individual::printIndividual()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("   ");
    for (int j=0;j<44;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=43)
            individualString.append("-");
    }
    individualString.append("|");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append("|");
    individualString.append(QString::number(getPerformanceLatency()));
    qDebug(qPrintable(individualString));
    //qDebug("Fo:%f",getPerformanceValue());
}

QString Individual::getIndividualAsQString()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("");
    for (int j=0;j<44;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=43)
            individualString.append("-");
    }
    individualString.append("|");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append("|");
    individualString.append(QString::number(getPerformanceLatency()));
    return individualString;
}

void Individual::setPerformanceValue(double performance)
{
    performanceValue = performance;
}


void Individual::calculatePerformanceValue()
{
    performanceValue = parametersList.at(2)+parametersList.at(5)+parametersList.at(8)+parametersList.at(11)+parametersList.at(14)+
            parametersList.at(17)+parametersList.at(20)+parametersList.at(23)+parametersList.at(26)+parametersList.at(29)+parametersList.at(32);

    // se deben calcular los valores de las funciones objetivo para el individuo


    // D = Sumatoria i=1,11 Pi*di
    performanceDiscovery = 0;


    performanceLatency = 0;


}

double Individual::getPerformanceValue()
{
    return performanceValue;
}


void Individual::setPerformanceDiscovery(double performance)
{
    performanceDiscovery = performance;
}


double Individual::getPerformanceDiscovery()
{
    return performanceDiscovery;
}

void Individual::setPerformanceLatency(double performance)
{
    performanceLatency = performance;
}


double Individual::getPerformanceLatency()
{
    return performanceLatency;
}




void Individual::setParameter(int i, double value)
{
    parametersList.replace(i,value);
}

double Individual::getParameter(int i)
{
    return parametersList.at(i);
}

int Individual::getNumberOfParameters()
{
    return parametersList.count();
}

void Individual::setWonMatchesCounter(int value)
{
    wonMatchesCounter = value;
}

int Individual::getWonMatchesCounter()
{
    return wonMatchesCounter;
}

void Individual::incrementWonMatchesCounter()
{
    wonMatchesCounter++;
}
