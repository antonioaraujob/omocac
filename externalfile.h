#ifndef EXTERNALFILE_H
#define EXTERNALFILE_H

#include "individual.h"


/**
 * Clase que modela el archivo externo de la optimizacion multiobjetivo
 * con algoritmo cultural
 */
class ExternalFile
{

private:

    /**
     * @brief Lista de individuos no dominados
     */
    QList<Individual *> externalFileNonDominatedList;

public:

    /**
    * Constructor de la clase
    */
    ExternalFile();

    /**
     * Destructor de la clase
     */
    ~ExternalFile();


    /**
    * Devuelve el limite inferior de la funcion objetivo 1 para los individuos
    * del archivo.
    *
    * @return Limite inferior de la funcion objetivo 1
    */
    double getLowerF1();

    /**
    * Devuelve el limite superior de la funcion objetivo 1 para los individuos
    * del archivo.
    *
    * @return Limite superior de la funcion objetivo 1
    */
    double getUpperF1();

    /**
    * Devuelve el limite inferior de la funcion objetivo 2 para los individuos
    * del archivo.
    *
    * @return Limite inferior de la funcion objetivo 2
    */
    double getLowerF2();

    /**
    * Devuelve el limite superior de la funcion objetivo 2 para los individuos
    * del archivo.
    *
    * @return Limite superior de la funcion objetivo 2
    */
    double getUpperF2();

    /**
     * @brief Retorna la lista con los individuos no dominados del archivo externo
     * @return Lista de individuos no dominados del archivo externo
     */
    QList<Individual *> getExternalFileList();

    /**
     * @brief Agregar el individuo pasado como argumento si cumple con las condiciones.
     *
     *
     *
     * @param ind individuo no dominado que se debe agregar al archivo externo
     */
    void addNonDominatedIndividuals(Individual * ind);


};

#endif // EXTERNALFILE_H
