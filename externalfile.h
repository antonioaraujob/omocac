#ifndef EXTERNALFILE_H
#define EXTERNALFILE_H

/**
 * Clase que modela el archivo externo de la optimizacion multiobjetivo
 * con algoritmo cultural
 */
class ExternalFile
{


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

};

#endif // EXTERNALFILE_H
