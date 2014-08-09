#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QObject>
#include <QList>
#include <QSet>

/**
 * Clase que modela un individuo del espacio de poblacion.
 *
 * Un individuo tiene la siguiente estructura:
 *
 * C_i|MinChannelTime_i|MaxChannelTime_i|AP_i|F1|F2
 *
 * con i= 1,...11. Donde:
 *
 * C_i: Canal i
 * MinChannelTime_i: parametro MinChannelTime para el canal i
 * MaxChannelTime_i: parametro MaxChannelTime para el canal i
 * AP_i: numero de APs en el canal i
 * F1: valor de la funcion objetivo 1 (Descubierta) para los parametros del individuo
 * F2: valor de la funcion objetivo 2 (Latencia) para los parametros del individuo
 *
 */
class Individual
{

private:

    /**
     *  Lista de parametros de un individuo
     */
    QList<double> parametersList;

    /**
     * Valor de desempeno del individuo
     */
    double performanceValue;

    /**
     * Valor de desempeno del individuo para la funcion objetivo 1 tasa de descubrimiento
     * de APs
     */
    double performanceDiscovery;

    /**
     * Valor de desempeno del individuo para la funcion objetivo 2 latencia de full scanning
     *
     */
    double performanceLatency;

    /**
     * Conjunto utilizado para generar secuencias de scanning aleatorias
     */
    QSet<int> channelSequenceSet;

public:
    /**
     * Constructor de la clase
     *
     * @param numberOfApsDeployed Numero de APs desplegados
     */
    Individual(int numberOfApsDeployed);

    /**
     * Destructor de la clase
     */
    ~Individual();

    /**
     * Constructor copia
     */
    Individual(Individual &p);

    /**
     * Retorna un numero de canal aleatorio.
     *
     * Esta funcion se utiliza para inicializar los individuos de manera que los canales
     * aleatorios seleccionados no se repitan en la secuencia de scanning.
     *
     * @return Numero de canal aleatorio
     */
    int getRandomChannel();

    /**
     * Retorna un numero de minChannelTime aleatorio
     * @return valor de minChannelTime aleatorio
     */
    double getRandomMinChannelTime();

    /**
     *  Retorna un numero de maxChannelTime aleatorio
     * @return canal aleatorio
     */
    double getRandomMaxChannelTime();

    /**
     * Retorna un numero de APs descubiertos en el canal i
     * dado un numero de AP desplegados.
     *
     * El valor se obtiene de la proporcion promedio de APs que operan en
     * cada canal.
     *
     * @param
     * @return Numero de APs descubiertos en el canal i
     */
    double getAPNumberOnChannel(int numberOfApsDeployed, int channel);

    /**
     *  Imprime el individuo en una cadena legible al humano
     */
    void printIndividual();

    /**
     * Retorna el individuo como una cadena
     * @return Cadena legible al humano de los parametros del individuo
     */
    QString getIndividualAsQString();

    /**
     *  Establece el valor de desempeno del individuo
     * @param performance valor de desempeno
     */
    void setPerformanceValue(double performance);

    /**
     *  Calcula el valor de desempeno del individuo
     */
    void calculatePerformanceValue();

    /**
     * Retorna el valor de desempeno del individuo
     * @return valor de desempeno del individuo
     */
    double getPerformanceValue();

    /**
     *  Establece el valor de desempeno de la funcion objetivo 1 tasa de descubrimiento
     * @param performance valor de desempeno
     */
    void setPerformanceDiscovery(double performance);

    /**
     * Retorna el valor de desempeno del individuo para la funcion objetivo 1 tasa de descubrimiento
     * @return valor de desempeno de la tasa de descubrimiento del individuo
     */
    double getPerformanceDiscovery();

    /**
     *  Establece el valor de desempeno de la funcion objetivo 2 latencia
     * @param performance valor de desempeno de latencia
     */
    void setPerformanceLatency(double performance);

    /**
     * Retorna el valor de desempeno del individuo para la funcion objetivo 2 latencia
     * @return valor de desempeno de la latencia
     */
    double getPerformanceLatency();

    /**
     * Asigna el valor del parametro en la posicion i
     * @param i indice del parametro a asignar
     * @param value valor a asignar en el parametro
     */
    void setParameter(int i, double value);

    /**
     * Retorna el valor del parametro en la posicion i
     * @param i indice del parametro a retornar
     */
    double getParameter(int i);

    /**
     * Retorna el numero de parametros del individuo
     * @return Numero de parametros del individuo
     */
    int getNumberOfParameters();


};

#endif // INDIVIDUAL_H
