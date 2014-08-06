#include "individual.h"

#include <QTime>

Individual::Individual()
{
    //qsrand((uint)QTime::currentTime().msec());

    // se deben crear los 33 parametros
    // C1,Min1,Max1,C2,Min2,Max2,...,C11,Min11,Max11
    for (int i=0; i<11; i++)
    {
        parametersList.append(getRandomChannel());
        parametersList.append(getRandomMinChannelTime());
        parametersList.append(getRandomMaxChannelTime());
    }

    // establecer el valor de desempeno en 0
    //setPerformanceValue(0);

    // calcular el valor de desempeno para el individuo
    calculatePerformanceValue();
}


Individual::Individual(Individual &p)
{
    for (int i=0; i<33; i++)
    {
        parametersList.append(p.getParameter(i));
    }
}

int Individual::getRandomChannel()
{
    // el rango es 1 <= channel <= 11
    int low = 1;
    int high = 11;
    return qrand() % ((high + 1) - low) + low;
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

void Individual::printIndividual()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("   ");
    for (int j=0;j<33;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=32)
            individualString.append("-");
    }
    individualString.append("|");
    individualString.append(QString::number(getPerformanceValue()));
    qDebug(qPrintable(individualString));
    //qDebug("Fo:%f",getPerformanceValue());
}

QString Individual::getIndividualAsQString()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("   ");
    for (int j=0;j<33;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=32)
            individualString.append("-");
    }
    individualString.append("|");
    individualString.append(QString::number(getPerformanceValue()));
    return individualString;
    //qDebug(qPrintable(individualString));
}

void Individual::setPerformanceValue(double performance)
{
    performanceValue = performance;
}


void Individual::calculatePerformanceValue()
{
    performanceValue = parametersList.at(2)+parametersList.at(5)+parametersList.at(8)+parametersList.at(11)+parametersList.at(14)+
            parametersList.at(17)+parametersList.at(20)+parametersList.at(23)+parametersList.at(26)+parametersList.at(29)+parametersList.at(32);

}

double Individual::getPerformanceValue()
{
    return performanceValue;
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
