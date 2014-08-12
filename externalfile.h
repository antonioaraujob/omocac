#ifndef EXTERNALFILE_H
#define EXTERNALFILE_H

#include "individual.h"
#include "normativegrid.h"



/**
 * Clase que modela el archivo externo de la optimizacion multiobjetivo
 * con algoritmo cultural
 */
class ExternalFile
{

private:

    /**
     * @brief Tamano maximo del archivo externo
     */
    int maxExternalFileSize;

    /**
     * @brief Lista de individuos no dominados
     */
    QList<Individual *> externalFileNonDominatedList;

public:

    /**
    * Constructor de la clase
    */
    ExternalFile(int externalFileSize);

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
     * @param ind individuo no dominado que se debe agregar al archivo externo
     */
    void addNonDominatedIndividuals(Individual * ind);

    /**
     * @brief Agrega los individuos no dominados de la lista pasada como argumento al archivo
     * externo.
     *
     * Se siguen las reglas para insertar los individuos en el archivl externo
     *
     * @param nonDominatedList Lista de individuos no dominados a agregar
     */
    void addNonDominatedIndividuals(QList<Individual *> nonDominatedListToInsert, NormativeGrid * nGrid);

    /**
     * @brief Retorna verdadero si el individuo pasado como argumento esta dominado por algun
     * individuo existente en el archivo externo.
     *
     * @param individual Individuo a verificar si es dominado
     * @return Verdadero si el individuo argumento esta dominado por algun individuo existente
     * en el archivo externo
     */
    bool isNewIndividualDominatedByExternalFile(Individual * newIndividual);

    /**
     * Retorna si el individuo xj domina al individuo xi
     * @param xj Individuo 1
     * @param xi Individuo 2
     * @return Verdadero si individuo xj domina a xi
     */
    bool individualDominate(Individual * xj, Individual * xi);

    /**
     * @brief Retorna verdadero si el individuo pasado como argumento domina a algun
     * individuo existente en el archivo externo.
     *
     * @param newIndividual Individuo para verificar si domina a alguno existente en el archivo externo
     * @return Verdadero si individuo pasado como argumento domina a algun individuo
     * existente en el archivo externo.
     */
    bool newIndividualDominatesAnyoneInExternalFile(Individual * newIndividual);

    /**
     * @brief Agrega un individuo que domina el archivo externo y sigue verificando si
     * hay otros individuos dominados para eliminarlos
     *
     * @param newIndividual Individuo para verificar si domina a alguno existente en el archivo externo
     */
    void addNewIndividualAndCheck(Individual * newIndividual);

    /**
     * @brief Retorna verdadero si el individuo pasado como argumento no domina a nadie ni nadie
     * lo domina a el
     *
     * @param newIndividual Individuo para verificar si domina a alguien o lo dominan a el
     */
    bool newIndividualNotDominatedNotDominates(Individual * newIndividual);

    /**
     * @brief Chequea el contador de la rejilla de los individuos del archivo externo para reemplazar uno
     * con el individuo pasado como argumento
     *
     * Se sigue la regla numero 4 de las reglas de insercion de individuos en el archivo externo
     *
     * @param newIndividual Individuo para verificar el reemplazo en el archivo externo
     * @param nGrid Rejilla del espacio de creencias
     */
    void checkGridCellAndInsertIndividual(Individual * newIndividual, NormativeGrid *nGrid);

    /**
     * @brief Retorna verdadero si el individuo pasado como argumento ya existe en el archivo externo
     *
     * @param ind individuo para verificar si existe en el archivo externo
     * @return Retorna verdadero si el individuo pasado como argumento ya existe en el archivo externo
     */
    bool isIndividualInExternalFile(Individual * ind);
};

#endif // EXTERNALFILE_H
