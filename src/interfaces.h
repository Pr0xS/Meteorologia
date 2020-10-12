/**
 * @file interfaces.h
 * @brief En este fichero están declaradas aquellas funciones que tienen como objetivo interactuar con el usuario
 * de la aplicación
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include "meteo.h"


/**
 * @fn int interactiveMenu(char * city, char * date, char * unit, int * days);
 * @brief La función interactiveMenu() solicita los datos necesarios para realizar una búsqueda.
 * @param city Se trata de un puntero a string (char *) donde se almacenará el nombre de la ciudad a buscar.
 * @param date Se trata de un puneteo a string (char *) donde se almacenará la fecha sobre la que se realizará
 * la previsión meteorológica.
 * @param unit Se trata de un puntero a string (char *) donde se almacenará la unidad de medida de la temparatura.
 * Por defecto devuelve 'C'.
 * @param days Se trata de un puntero a int (int *) donde se amacenará el número de días de los que obtener la
 * previsíon meteorológica. Por defecto devuelve 5.
 * @param printJSON Se trata de un puntero a entero (int *) donde se almacenará si se desea mostrar la información por
 * pantalla en formato '.json'. El valor será 1 en caso afirmativo y 0 en caso negativo. Por defecto devuelve 0.
 * @param saveJSON Se trata de un punteo a entero (int *) donde se almacenará si se desea guardar la información en un
 * fichero '.json'. El valor será 1 en caso afirmativo y 0 en caso negativo. Por defecto devuelve 1.
 * @return La función interactiveMenu() devuele un entero con el valo 0 en caso de éxito y un -1 en caso de error.
 */
int interactiveMenu(char * city, char * date, char * unit, int * days, int * printJSON, int * saveJSON);


/**
 * @fn int showForecast(struct Meteo * forecast, int n_data, char unit);
 * @brief La función showForecast() imprime por pantalla la información meteorológica proporcionada.
 * @param forecast Se trata de un array de estructuras de tipo Meteo (struct Meteo *) que contiene la información
 * meteorológica.
 * @param n_data Se trata de un entero que contiene la cantidad de entradas meteorológicas que contiene el array
 * forecast.
 * @param unit Se trata de una char que contiene la unidad en la que se representarán las unidades. Estas pueden ser
 * 'C' para Celsius o 'F' para Fahrenheit.
 * @return La función showForecast devuelve un entero con valor 0 si se ha ejecutado con éxito, y un -1 si se ha
 * producido un error.
 */
int showForecast(struct Meteo * forecast, int n_data, char unit);


#endif /* INTERFACES_H */