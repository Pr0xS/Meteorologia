/**
 * @file helpers.h
 * @brief En este fichero están declaradas aquellas funciones cuyo objetivo es de caracter general y pueden
 * ser invocadas en multiples situaciones.
 */

#ifndef HELPERS_H
#define HELPERS_H


/**
 * @fn char ** split(char * string, const char delimiter);
 * @brief La función split() divide el string recibido en substring utilizando como divisor un delimitador.
 * Ejemplo split("Esto es una prueba", ' ') obtendriamos un array con 4 strings "Esto", "es", "una", "prueba".
 * @param string Se trata de un string (char *) que contiene la string que se quiere dividir.
 * @param delimiter Se trata de un caracter (char) que contiene el delimitador por el cual se dividirá el string.
 * @return La función split() devuelve un array de strings (char **) en el cual cada posición del array contiene
 * una de las divisiones del string introducido.
 * @warning Es necesario liberar la memoria reservada por la funcion split() del parametro devuelto. Para ello
 * liberaremos la memoria reservada para cada string devuelto en el array y luego liberaremos la memoria del array.
 */
char ** split(char * string, const char delimiter);


/**
 * @fn void fixDecimalNotation(char * string);
 * @brief La función fixDecimalNotation() corrige la notación de los números decimales. Sustituye los decimales
 * expresados con ',' por '.'
 * Ejemplo: 12,23 -> 12.23
 * @param string Se trata de un string (char *) que contiene el número al que se le quiere corregir
 * el simbolo de decimal.
 */
void fixDecimalNotation(char * string);


/**
 * @fn void trim(char * string);
 * @brief La función trim() elimina los espacios en blanco ' ' y otros caracters especiales tanto al comienzo
 * como al final del string recibido.
 * @param string Se trata de un string (char *) a la que le queremos quitar los espacios en blanco.
 */
void trim(char * string);


/**
 * @fn int getIntFromUserInput(int * number);
 * @brief La función getIntFromUserInput() recibe una entrada por teclado y la convierte en INT cuando sea 
 * posible.
 * @param number Se trata de un puntero a entero (int *) en el cuál se almacenará el número recibido.
 * @return La función devuelve un 0 en caso de que se haya podido recibir y convertir la entrada a entero.
 * En caso de error, devolverá -1.
 */
int getIntFromUserInput(int * number);


/**
 * @fn int getStringFromUserInput(char * string, int size);
 * @brief La función getStringFromUserInput() recibe una entrada por teclado y la almacena.
 * @param string Se trata de un string (char *) en el cuál se almacenará el la cadena
 * de texto recibida.
 * @param size Entero con la tamaño máximo de la cadena que se desea recibir.
 * @return La función devuelve un entero indicando la longitud del string recibido. En caso de error
 * devolverá -1.
 */
int getStringFromUserInput(char * string, int size);


/**
 * @fn int compareString(void const * str1, void const *str2);
 * @brief La función compareString() compara dos string. Internamente utiliza la funcion strcmp(). La 
 * razón de ser de esta función es para utilizarla como comparador en la función de ordenación qsort()
 * @param str1 Se trata de un string (char *) que contiene la primera string a comparar.
 * @param str2 Se trata de un string (char *) que contiene la segunda string a comparar.
 * @return Si str1 > str2 devuelve un número positivo;
 * Si str1 < str2 devuelve un número negativo;
 * Si str1 == str2 devuelve un cero;
 */
int compareString(void const * str1, void const *str2);


/**
 * @fn int compareDates(char * date1, char* date2);
 * @brief La función compareDates() compara dos fechas en formato AAAA/MM/DD (Año/Mes/Día)
 * @param date1 Se trata de un string (char *) que contiene la primera fecha a comparar.
 * @param date2 Se trata de un string (char *) que contiene la segunda fecha a comparar.
 * @return Si date1 > date2 devuelve un 1;
 * Si date1 < date2 devuelve un -1;
 * Si date1 == date2 devuelve un 0;
 */
int compareDates(char * date1, char* date2);


/**
 * @fn int strCelsiusToStrFahrenheit(char * Celsius, char ** Fahrenheit);
 * @brief La función strCelsiusToStrFahrengeit() recibe grados celsiud en formato string para transofrmalor
 * en grados Fahrenheit también en formato string
 * @param celsius Se trata de un string (char *) que contiene los grados celsiud a convertir
 * @param fahrenheit Se trata de un puntero a string (char **) que contendrá el resultado de la conversión de Celsiud a 
 * Fahrenheit
 * @return La función strCelsiudToStrFahrenheit() devuelve un entero con valor 0 si la operación a resultado
 * con éxito y un -1 si se produce un error.
 * @warning Es necesario liberar la memoria reservada por la función strCelsiusToStrFahrenheit(). Para ello
 * liberaremos la mermoria del puntero a string fahrenheit. 
 */
int strCelsiusToStrFahrenheit(char * celsius, char ** fahrenheit);


/**
 * @fn int stringToFloat(double * value, char * data)
 * @brief La función stringToFloat() convierte una cadena de caracteres en float si es posible.
 * @param value Se trata de un double donde se almacenará el número en caso de éxito;
 * @param data Se trata de un string (char *) que contiene los datos que se desean convertir
 * @return La función stringToFloat devuelve un entero con un 0 en caso de éxito y un -1 si hay algún error.
 */
int stringToFloat(double * value, char * data);

/**
 * @fn double celsiusToFahrenheit(double celsius);
 * @brief La función celsiusToFahrenheit convierte los grados Celius introducidos en Fahrenheit
 * @param celsius Se trata de un double que contiene los grados celsius a convertir
 * @return La función celsiusToFahrenheit devuelve un double con la conversión de Celsius a Fahrenheit
 */
double celsiusToFahrenheit(double celsius);


/**
 * @fn int storeToFile(char * filename, char * data);
 * @brief La función storeToFile() almacena en un fichero los datos proporcionados. Esta función creará
 * el fichero si no existe o lo sobreescribirá en caso de que existiera
 * @param filename Se trata de un string (char *) que contiene el nombre del fichero donde se va a guardar los datos
 * @param data Se trata de un string (char *) que contiene los datos que se van a almancenar en el fichero
 * @return La función storeToFile devuelve un entero con un valor de 0 en caso de éxito y un -1 en caso
 * de error
 */
int storeToFile(char * filename, char * data);


/**
 * @fn int replace(char * string, char c1, char c2);
 * @brief La función replace(), reemplaza la el caracter c1 por c2 en toda la string
 * @param string Se trata de un string que contiene los caracteres que se quieren reemplazar
 * @param c1 Se trata de caracter que se quiere reemplazar por otro
 * @param c2 Se trata de caracter por el cuál se va a reemplazar
 */
void replace(char * string, char c1, char c2);


#endif /* HELPERS_H */