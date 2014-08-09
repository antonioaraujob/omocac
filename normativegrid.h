#ifndef NORMATIVEGRID_H
#define NORMATIVEGRID_H



#include "individual.h"
#include "normativephenotypicpart.h"
#include "gridsubinterval.h"


// Clase que modela la rejilla (grid) del espacio de creencias
class NormativeGrid
{

private:

    /**
     * Numero de intervalos para construir la rejilla
     */
    int subIntervalNumber;

    /**
     * @brief Lista de subintervalos de la funcion objetivo 1
     */
    QList<GridSubInterval *> subIntervalListF1;

    /**
     * @brief Lista de subintervalos de la funcion objetivo 2
     */
    QList<GridSubInterval *> subIntervalListF2;

    /**
     * Rejilla del espacio de creencias
     *
     * En el eje X estaran los valores de la funcion objetivo 1 descubierta
     * En el eje Y estaran los valores de la funcion objetivo 2 latencia
     */
    int ** ptrGrid;

public:

    /**
     * Constructor de la clase NormativeGrid
     *
     * @param intervals corresponde al numero de intervalos en que se divide la rejilla (intervals x intervals)
     * @param nPhenotypicPart corresponde a la parte normativa fenotipica
     */
    NormativeGrid(int subIntervals, NormativePhenotypicPart * nPhenotypicPart);

    /**
     * Destructor de la clase NormativeGrid
     */
    ~NormativeGrid();

    /**
     * Retorna el numero de intervalos para dividir la rejilla
     * @return intervalos para dividir la rejilla
     */
    int getSubIntervalNumber();

    /**
     * Agrega un individuo a la grid.
     *
     * Se incrementa el contador en la celda de la grid correspondiente al individuo.
     *
     * @param individuo a agregar
     */
    void addIndividualToGrid(Individual * ind);

    /**
     * Retorna el contador de individuos en una celda (x,y)
     *
     * @param f1 valor de la funcion objetivo 1
     * @param f2 valor de la funcion objetivo 2
     *
     * @return contador de individuos en la celda
     */
    int getCount(int f1, int f2);

    /**
     * @brief Construye los subintervalos de la rejilla para la funcion objetivo 1
     */
    void buildSubintervalsF1(NormativePhenotypicPart * nPhenotypicPart);

    /**
     * @brief Construye los subintervalos de la rejilla para la funcion objetivo 1
     */
    void buildSubintervalsF2(NormativePhenotypicPart * nPhenotypicPart);


    /**
     * @brief Retorna el indice del subintervalo de la funcion objetivo 1 a la que pertenece el
     * valor pasado como argumento.
     *
     * El indice retornado sigue la enumeracion desde 0 como en los vectores de C.
     *
     * @param value valor del cual se desea conocer el subintervalo al que pertenece
     * @return indice del subintervalo al que pertenece el valor pasado como argumento.
     */
    int getF1SubintervalIndex(double value);

    /**
     * @brief Retorna el indice del subintervalo de la funcion objetivo 2 a la que pertenece el
     * valor pasado como argumento.
     *
     * El indice retornado sigue la enumeracion desde 0 como en los vectores de C.
     *
     * @param value valor del cual se desea conocer el subintervalo al que pertenece
     * @return indice del subintervalo al que pertenece el valor pasado como argumento.
     */
    int getF2SubintervalIndex(double value);

    /**
     * @brief Imprime el contenido de la rejilla
     */
    void printGrid();

};

#endif // NORMATIVEGRID_H
