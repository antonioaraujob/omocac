#ifndef NORMATIVEPHENOTYPICPART_H
#define NORMATIVEPHENOTYPICPART_H

#include "externalfile.h"


/**
 * Clase que modela la Parte Fenotipica Normativa.
 *
 * Mantiene los limites inferior y superior de los intervalos de cada funcion
 * objetivo dentro de los cuales se construira una rejilla (NormativeGrid).
 *
 */
class NormativePhenotypicPart
{

private:


    /**
     * Limite inferior de la funcion objetivo 1
     */
    double lowerF1;

    /**
     * Limite superior de la funcion objetivo 2
     */
    double upperF1;

    /**
     * Limite inferior de la funcion objetivo 2
     */
    double lowerF2;

    /**
     * Limite superior de la funcion objetivo2
     */
    double upperF2;


public:

    /**
     * Constructor de la clase
     */
    NormativePhenotypicPart();

    /**
     * Constructor de la clase
     * @param lF1 limite inferior de la funcion objetivo 1
     * @param uF1 limite superior de la funcion objetivo 1
     * @param lF2 limite inferior de la funcion objetivo 2
     * @param uF2 limite superior de la funcion objetivo 2
     */
    NormativePhenotypicPart(int lF1, int uF1, int lF2, int uF2);

    /**
     * Destructor de la clase
     */
    ~NormativePhenotypicPart();

    /**
     * Establece el valor lowerF1
     *
     * @param lF1 limite inferior a establecer
     */
    void setLowerF1(double lF1);

    /**
     * Devuelve el valor lowerF1
     *
     * @return el limite inferior de la funcion objetivo 1
     */
    double getLowerF1();

    /**
     * Establece el valor upperF1
     *
     * @param uF1 limite superior a establecer
     */
    void setUpperF1(double uF1);

    /**
     * Devuelve el valor upperF1
     *
     * @return el limite superior de la funcion objetivo 1
     */
    double getUpperF1();

    /**
     * Establece el valor lowerF2
     *
     * @param lF1 limite inferior a establecer
     */
    void setLowerF2(double lF2);

    /**
     * Devuelve el valor lowerF2
     *
     * @return el limite inferior de la funcion objetivo 2
     */
    double getLowerF2();

    /**
     * Establece el valor upperF2
     *
     * @param uF2 limite superior a establecer
     */
    void setUpperF2(double uF2);

    /**
     * Devuelve el valor upperF2
     *
     * @return el limite superior de la funcion objetivo 2
     */
    double getUpperF2();

    /**
     * Actualiza la parte fenotipica normativa
     * @param lF1 limite inferior de la funcion objetivo 1
     * @param uF1 limite superior de la funcion objetivo 1
     * @param lF2 limite inferior de la funcion objetivo 2
     * @param uF2 limite superior de la funcion objetivo 2
     */
    void updateNormativePhenotypicPart(double lF1, double uF1, double lF2, double uF2);

    /**
     * Actualiza la parte fenotipica normativa de acuerdo al contenido del archivo externo
     * pasado como argumento.
     *
     * @param extFile ExternalFile para obtener los limites de las funciones objetivo
     */
    void updateNormativePhenotypicPart(ExternalFile extFile);



};

#endif // NORMATIVEPHENOTYPICPART_H
