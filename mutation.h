#ifndef MUTATION_H
#define MUTATION_H

#include <QList>

#include "individual.h"

/**
 * Clase que modela la variacion de la poblacion para cada generacion
 */
class Mutation
{

private:
    /**
     * Lista que mantiene la poblacion original mas los hijos generados
     */
    QList<Individual *> newPopulation;


public:

    /**
     * @brief Constructor de la clase Mutation
     */
    Mutation();

    /**
     * @brief Destructor de la clase Mutation
     */
    ~Mutation();

    /**
     * @brief Ejecuta el proceso de mutacion sobre la poblacion pasada como argumento
     * @param population poblacion sobre la cual se ejecuta el proceso de mutacion
     * @param sKnowledge
     * @param nKnowledge
     * @param std desviacion estandar de la variable aleatoria normal
     */
    void doMutation(QList<Individual *> population, double std);


    /**
     * @brief Retorna la nueva poblacion luego de la variacion.
     *
     * Esta poblacion es de tamano 2P
     * @return Lista de tamano 2P con la nueva poblacion luego de ejecutada la mutacion
     */
    QList<Individual *> getNewPopulation();

    /**
     * Retorna un numero aletorio entre a y b
     *
     * @param a limite inferior
     * @param b limite superior
     * @return numero aleatorio entre a y b
     */
    int getRandom(int low, int high);

    /**
     * @brief Ejecuta una mutacion gausiana de un parametro de un individuo
     * @param index indice del parametro a mutar
     * @param mean media de la distribucion normal
     * @param std desviacion estandar de la distribucion normal
     * @return valor del parametro mutado
     */
    int mutateIndividualParameter(int index, int mean, double std);

    /**
     * @brief Retorna verdadero si el parametro a revisar de un individuo corresponde a un canal
     * @param index indice del parametro a revisar del individuo
     * @return Verdadero si el indice corresponde a un parametro de numero de canal
     */
    bool isThisParameterAChannel(int index);

    /**
     * @brief Retorna verdadero si el parametro a revisar de un individuo corresponde a un MinChannelTime
     * @param index indice del parametro a revisar del individuo
     * @return Verdadero si el indice corresponde a un parametro de MinChannelTime
     */
    bool isThisParameterAMinChannelTime(int index);

    /**
     * @brief Retorna verdadero si el parametro a revisar de un individuo corresponde a un MaxChannelTime
     * @param index indice del parametro a revisar del individuo
     * @return Verdadero si el indice corresponde a un parametro de MaxChannelTime
     */
    bool isThisParameterAMaxChannelTime(int index);

    /**
     * @brief Retorna verdadero si el parametro a revisar de un individuo corresponde a numero de APs
     * @param index indice del parametro a revisar del individuo
     * @return Verdadero si el indice corresponde a un parametro de APs
     */
    bool isThisParameterAPs(int index);

};

#endif // MUTATION_H
