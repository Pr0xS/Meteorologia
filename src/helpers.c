/**
 * @file helpers.c
 * @brief En este fichero están definidas las funciones declaradas en helpers.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "helpers.h"


char ** split(char * string, const char delimiter) {
    unsigned int length = strlen(string);
    int counter = 0;

    // Contador necesario para saber cuanto espacio reservaremos
    for (int i = 0; i < length; i++) {
        if (string[i] == delimiter) {
            counter++;
        }
    }
    counter++;

    // Reservamos espacio para el numero de divisiones que se crearán
    char ** array = (char **)malloc((counter + 1) * sizeof(char *));

    // Guardamos una referencia al inicio del array
    char ** base = array;

    for (int i = 0; i < counter; i++) {
        int offset = 0;

        // Contamos el número de caracteres que seran necesarios reservar en memoria
        while (string[offset] != delimiter && string[offset] != '\0') {
            offset++;
        }
        offset ++;

        // Reservamos la memoria y copiamos el strig delimitado
        *array = (char *)malloc(sizeof (char *) * offset);
        memcpy(*array, string, offset);
        (*array)[offset-1] = '\0';
        string += offset;
        array++;
    }

    // Limpiamos el puntero que nos ha servido para iterar sobre el string
    *array = NULL;
    return base;
}


void fixDecimalNotation(char * string) {
    unsigned int length = strlen(string);

    // Buscamos y reemplazamos el la primera coma por un punto
    for (int i = 0; i < length; i++) {
        if (string[i] == ',') {
            string[i] = '.';
            return;
        }
        else if (string[i] == '.') {
            return;
        }
    }
}


void trim(char * string) {
    unsigned int walker = strlen(string);

    // Quitamos espacios al final
    while (walker > 0 && isspace(string[walker - 1])) { // Según el manual isspace detecta también '\f', '\n', '\r', '\r' y '\v'
        walker--;
    }
    string[walker] = '\0';

    // Quitamos espacios al principio
    walker = strspn(string, " \t\n\v");
    memmove(string, string + walker, strlen(string + walker) + 1);  // + 1 necesario para copiar \0
}


int getIntFromUserInput(int * number) {
    long lnumber;
    char buffer[1024];
    char * end;

    // Error al leer la entrada:
    if (!fgets(buffer, 1024, stdin)) {
        return -1;
    }

    trim(buffer);

    // El buffer está vacío
    if (strlen(buffer) == 0) {
        return -1;
    }

    lnumber = strtol(buffer, &end, 10);

    if ((lnumber > INT_MAX) || (lnumber < INT_MIN)) {
        // El número es demasiado grande para el tipo int
        return -1;
    } else if ( *end && *end != '\n') {
        // No se ha leido el buffer entero
        return -1;
    }

    *number = (int)lnumber;

    return 0;
}


int getStringFromUserInput(char * string, int size) {
    char buffer[size];

    if (!fgets(buffer, size, stdin)) {
        // Error al leer la entrada:
        return -1;
    }

    // Reiniciamos el puntero de stdin en el caso de que todavia quede algo el el buffer
    fseek(stdin,0,SEEK_END);

    // En caso de que se haya introducido un \n se elimina.
    buffer[strcspn(buffer, "\n")] = 0;

    strcpy(string, buffer);
    return strlen(buffer);
}


int compareString(void const * str1, void const *str2) {
    char const * a = (char const *) str1;
    char const * b = (char const *) str2;
    return strcmp(a, b);
}


int compareDates(char * date1, char* date2) {
    char ** date_1 = split(date1, '/');
    char ** date_2 = split(date2, '/');

    int num1, num2;
    int i = 0;

    int cmp = 0;

    // Transformamos los string a enteros y los comparamos
    while (date_1[i] && date_2[i]) {
        num1 = atol(date_1[i]);
        num2 = atol(date_2[i]);
        if (num1 > num2) {
            cmp = 1;
            break;
        } else if (num1 < num2) {
            cmp = -1;
            break;
        }
        i++;
    }

    // Liberamos memoria
    i = 0;
    while (date_1[i] && date_2[i]) {
        free(date_1[i]);
        free(date_2[i]);
        i++;
    }

    free(date_1);
    free(date_2);
    date_1 = NULL;
    date_2 = NULL;

    return cmp;
}


int strCelsiusToStrFahrenheit(char * celsius, char ** fahrenheit) {
    double celsius_f, fahrenheit_f;
    char aux[100];
    int size = 0;

    if (stringToFloat(&celsius_f, celsius) != 0) {
        // Error al convertir los datos de string a float para procesarlos.
        return -1;
    }

    fahrenheit_f = celsiusToFahrenheit(celsius_f);

    size = sprintf(aux, "%.2f", fahrenheit_f);
    if (size < 0) {
        // Error al convertir el float en string
        return -1;
    }

    *fahrenheit = malloc(size * sizeof(char));
    strcpy(*fahrenheit, aux);

    return 0;
}


int stringToFloat(double * value, char * data) {
    double fnumber;
    char * end;

    trim(data);

    // El buffer está vacío
    if(strlen(data) == 0) {
        return -1;
    }

    fnumber = strtof(data, &end);

    if (*end && *end != '\n') {
        // El bufer no se ha leido entero
        return -1;
    }

    *value = fnumber;
    return 0;
}


double celsiusToFahrenheit(double celsius) {
    return celsius * 9/5 + 32;
}


int storeToFile(char * filename, char * data) {
    FILE * stream = fopen(filename, "w");

    if (stream == NULL) {
        perror("Error opening the file");
        return -1;
    }

    fputs(data, stream);

    fclose(stream);

    return 0;
}


void replace(char * string, char c1, char c2) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == c1) {
            string[i] = c2;
        }
    }
}