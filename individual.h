#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QObject>
#include <QList>
#include <QSet>

/**
 * @brief Clase que modela un individuo del espacio de poblacion.
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
     * @brief Constructor de la clase
     *
     * @param numberOfApsDeployed Numero de APs desplegados
     */
    Individual(int numberOfApsDeployed);

    /**
     * @brief Destructor de la clase
     */
    ~Individual();

    /**
     * @brief Constructor copia
     */
    Individual(Individual &p);

    /**
     * @brief Retorna un numero de canal aleatorio.
     *
     * Esta funcion se utiliza para inicializar los individuos de manera que los canales
     * aleatorios seleccionados no se repitan en la secuencia de scanning.
     *
     * @return Numero de canal aleatorio
     */
    int getRandomChannel();

    /**
     * @brief Retorna un numero de minChannelTime aleatorio
     * @return valor de minChannelTime aleatorio
     */
    double getRandomMinChannelTime();

    /**
     *  @brief Retorna un numero de maxChannelTime aleatorio
     * @return canal aleatorio
     */
    double getRandomMaxChannelTime();

    /**
     * @brief Retorna un numero de APs descubiertos en el canal i
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
     *  @brief Imprime el individuo en una cadena legible al humano
     */
    void printIndividual();

    /**
     * @brief Retorna el individuo como una cadena
     * @return Cadena legible al humano de los parametros del individuo
     */
    QString getIndividualAsQString();

    /**
     *  @brief Establece el valor de desempeno del individuo
     * @param performance valor de desempeno
     */
    void setPerformanceValue(double performance);

    /**
     *  @brief Calcula el valor de desempeno del individuo
     */
    void calculatePerformanceValue();

    /**
     * @brief Retorna el valor de desempeno del individuo
     * @return valor de desempeno del individuo
     */
    double getPerformanceValue();

    /**
     *  @brief Establece el valor de desempeno de la funcion objetivo 1 tasa de descubrimiento
     * @param performance valor de desempeno
     */
    void setPerformanceDiscovery(double performance);

    /**
     * @brief Retorna el valor de desempeno del individuo para la funcion objetivo 1 tasa de descubrimiento
     * @return valor de desempeno de la tasa de descubrimiento del individuo
     */
    double getPerformanceDiscovery();

    /**
     *  @brief Establece el valor de desempeno de la funcion objetivo 2 latencia
     * @param performance valor de desempeno de latencia
     */
    void setPerformanceLatency(double performance);

    /**
     * @brief Retorna el valor de desempeno del individuo para la funcion objetivo 2 latencia
     * @return valor de desempeno de la latencia
     */
    double getPerformanceLatency();

    /**
     * @brief Asigna el valor del parametro en la posicion i
     * @param i indice del parametro a asignar
     * @param value valor a asignar en el parametro
     */
    void setParameter(int i, double value);

    /**
     * @brief Retorna el valor del parametro en la posicion i
     * @param i indice del parametro a retornar
     */
    double getParameter(int i);

    /**
     * @brief Retorna el numero de parametros del individuo
     * @return Numero de parametros del individuo
     */
    int getNumberOfParameters();


};

#endif // INDIVIDUAL_H
