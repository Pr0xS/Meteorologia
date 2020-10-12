/**
 * @file meteo.c
 * @brief En este fichero están definidas las funciones declaradas en meteo.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meteo.h"
#include "helpers.h"

#define CITIES_BUFFER_INCREMENT 5
#define METEODATA_BUFFER_INCREMENT 10


void printMeteoEntry(struct Meteo meteoData) {
    printf("Fecha: %s, Ciudad: %s, Max Temp: %s, Min Temp: %s, Precipitaciones: %s, Nubosidad: %s\n", meteoData.date, meteoData.city, meteoData.max_temp, meteoData.min_temp, meteoData.precipitations, meteoData.cloudiness);
    // printf("Fecha: %s, Ciudad: %s, Max Temp: %f, Min Temp: %f, Precipitaciones: %f, Nubosidad: %i\n", meteoData.date, meteoData.city, meteoData.max_temp, meteoData.min_temp, meteoData.precipitations, meteoData.cloudiness);
}


int loadData(const char * filename, struct City ** cities) {
    int n_cities = 0;
    int cities_buffer = CITIES_BUFFER_INCREMENT;
    int city_exist = 0;
    struct Meteo meteoData;
    char line[1024];

    FILE * stream = fopen(filename, "r");

    // Comprobamos si se ha podido abrir el fichero
    if (stream == NULL) {
        printf("[-] Error al abir el fichero\n");
        return(-1);
    }

    // Reservamos memoria para las ciudades
    *cities = malloc(cities_buffer * sizeof(struct City));


    // Cargamos daos desde el fichero
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream)) {
        // Cargamos los datos en una estructura para facilitar su manipulación
        meteoData = customMeteoDataParser(line);

        // Comprobamos si la ciudad que hemos cargado la tenemos ya almacenada.
        for (int i = 0; i < n_cities; i++) {
            if (strcmp((*cities)[i].city, meteoData.city) == 0) {
                // Comprobamos si queda espacio libre. Si no queda, se reserva más.
                // Las reservas se hacen en incrementos de METEODATA_BUFFER_INCREMENT
                if ((*cities)[i].n_meteoData_entries >= (*cities)[i].memory_reserved) {
                    (*cities)[i].meteoData_array = realloc((*cities)[i].meteoData_array, ((*cities)[i].memory_reserved + METEODATA_BUFFER_INCREMENT) * sizeof(struct Meteo));
                    (*cities)[i].memory_reserved += METEODATA_BUFFER_INCREMENT;
                }

                // Almacenamos la estructura en la ciudad que corresponde
                (*cities)[i].meteoData_array[(*cities)[i].n_meteoData_entries] = meteoData;
                (*cities)[i].n_meteoData_entries++;

                city_exist = 1;
            }
        }
        
        // En caso de no haber encontrado la ciudad, la creamos.
        if (city_exist == 0) {
            // Comprobamos que queda espacio libre para la ciudad. Si no queda, se reserva más
            // Las reservas se hacen en incrementos de CITIES_BUFFER_INCREMENT
            if (n_cities >= cities_buffer) {
                *cities = realloc(*cities, (cities_buffer + CITIES_BUFFER_INCREMENT) * sizeof(struct City));
                cities_buffer += CITIES_BUFFER_INCREMENT;
            }

            // Almacenamos la ciudad nueva y almacenamos los primeros datos de la ciudad
            (*cities)[n_cities].meteoData_array = malloc(METEODATA_BUFFER_INCREMENT * sizeof(struct Meteo));
            strcpy((*cities)[n_cities].city, meteoData.city);
            (*cities)[n_cities].meteoData_array[0] = meteoData;
            (*cities)[n_cities].n_meteoData_entries = 1;
            (*cities)[n_cities].memory_reserved = METEODATA_BUFFER_INCREMENT;
            n_cities++;
        }

        city_exist = 0;
    }

    // Cerramos el ficher de texto
    fclose(stream);

    // Ordenamos las ciudades alfabeticamente
   qsort(*cities, n_cities, sizeof(struct City), &compareString);
    // qsort(*cities, n_cities, sizeof(struct City), (int (*)(const void*, const void *))strcmp);

    return n_cities;
}


struct Meteo customMeteoDataParser(char * line) {
    struct Meteo meteoLineData;

    char ** dataArray;

    dataArray = split(line, ';');

    // Fecha
    trim(dataArray[0]);
    strcpy(meteoLineData.date, dataArray[0]);

    // Ciudad
    trim(dataArray[1]);
    strcpy(meteoLineData.city, dataArray[1]);

    // Temperatura maxima
    trim(dataArray[2]);
    if (dataArray[2][0] != '\0') {
        fixDecimalNotation(dataArray[2]);
        strcpy(meteoLineData.max_temp, dataArray[2]);
    } else {
        strcpy(meteoLineData.max_temp, "No Data");
    }
    // meteoLineData.max_temp = atof(dataArray[2]);

    // Temperatura minima
    trim(dataArray[3]);
    if (dataArray[3][0] != '\0') {
        fixDecimalNotation(dataArray[3]);
        strcpy(meteoLineData.min_temp, dataArray[3]);
    } else {
        strcpy(meteoLineData.min_temp, "No Data");
    }
    // meteoLineData.min_temp = atof(dataArray[3]);

    // Precipitaciones
    trim(dataArray[4]);
    if (dataArray[4][0] != '\0') {
        fixDecimalNotation(dataArray[4]);
        strcpy(meteoLineData.precipitations, dataArray[4]);
    } else {
        strcpy(meteoLineData.precipitations, "No Data");
    }
    // meteoLineData.precipitations = atof(dataArray[4]);

    // Nubosidad
    trim(dataArray[5]);
    if (dataArray[5][0] != '\0') { // Comprobamos que no esté vacio
        fixDecimalNotation(dataArray[5]);
        strcpy(meteoLineData.cloudiness, dataArray[5]);
    } else {
        strcpy(meteoLineData.cloudiness, "No Data");
    }
    // meteoLineData.cloudiness = atoi(dataArray[5]);

    // Liberamos la memoria
    int i = 0;
    while (dataArray[i]) {
        free(dataArray[i]);
        i++;
    }
    free(dataArray);
    dataArray = NULL;

    return meteoLineData;
}


int binarySearchCities(char * city, struct City * cities, int numCities) {
    int left = 0;
    int middle = 0;
    int right = numCities;

    int cmp;

    while (left <= right) {
        middle = left + (right - left) / 2;
        cmp = strcmp(cities[middle].city, city);

        // Ciudad encontrada
        if (cmp == 0) {
            return middle;
        }

        // La ciudad es mayor, ignoramos la mitad izquieda
        if (cmp < 0) {
            left = middle + 1;
        }

        // La ciudad es menor, ignoramos la mitad derecha
        if (cmp > 0) {
            right = middle -1;
        }
    }

    // No se ha encontrado la ciudad
    return -1;
}


int binarySearchDates(char * date, struct Meteo * meteoData, int numDataEntries) {
    int left = 0;
    int middle = 0;
    int right = numDataEntries;

    int cmp;

    while (left <= right) {
        middle = left + (right - left) / 2;
        char * test = meteoData[middle].date;
        cmp = compareDates(test, date);

        // Fecha encontrada
        if (cmp == 0) { 
            return middle;
        }

        // La fecha es mayor, ignoramos la mitad izquierda
        if (cmp < 0) {
            left = middle + 1;
        }

        // La fecha es menor, ignoramos la mitad derecha
        if (cmp > 0) {
            right = middle - 1;
        }
    }

    // No se ha encontrado la fecha
    return -1;
}


int getForecast(struct City * cities, int numCities, struct Meteo ** forecast, char * city, char * date, int days) {
    int city_id, meteoData_id;
    int days_found = 0;

    (*forecast) = malloc(days * sizeof(struct Meteo));

    if ((city_id = binarySearchCities(city, cities, numCities)) == -1) {
        // Ciudad no encontrada
        return -1;
    } 

    if ((meteoData_id = binarySearchDates(date, cities[city_id].meteoData_array, cities[city_id].n_meteoData_entries)) == -1) {
        // Fecha no encontrada para la ciudad seleccionada;
        return -2;
    }

    for (int i = meteoData_id; i < meteoData_id + days && i < cities[city_id].n_meteoData_entries; i++) {
        (*forecast)[days_found] = cities[city_id].meteoData_array[i];
        days_found++;
    }

    return days_found;
}


int meteoDataToJSON(struct Meteo * meteoData, int meteoDataLength, char ** jsonData, char unit) {
    int memoryToReserve = 0;
    int bufferSize;

    memoryToReserve = strlen("[  ]\n");
    memoryToReserve += meteoDataLength * strlen("{ \"date\" : \"\", \"city\" : \"\", \"maxTemp_X\" : \"\", \"minTemp_X\" : \"\", \"precipitations_mm\" : \"\" , \"cloudiness_%%\" : \"\"}");

    memoryToReserve += 350; // 350 viene de la cantidad máxima de caracteres que la estructura Meteo puede almacenar

    *jsonData = malloc(memoryToReserve * sizeof(char));

    bufferSize = sprintf(*jsonData, "[ ");
    if (unit == 'C') {
        for (int i = 0; i < meteoDataLength; i++) {
            bufferSize += sprintf(*jsonData + bufferSize, "{ \"date\" : \"%s\", \"city\" : \"%s\", \"maxTemp_C\" : \"%s\", \"minTemp_C\" : \"%s\", \"precipitations_mm\" : \"%s\" , \"cloudiness_%%\" : \"%s\"}", meteoData[i].date, meteoData[i].city, meteoData[i].max_temp, meteoData[i].min_temp, meteoData[i].precipitations, meteoData[i].cloudiness);
            // Agrega una "," si no es final de línea
            if (i < (meteoDataLength - 1)) {
                bufferSize += sprintf(*jsonData + bufferSize, ", ");
            }
        }
    } else {
        for (int i = 0; i < meteoDataLength; i++) {
            char * minTempF, * maxTempF;
            strCelsiusToStrFahrenheit(meteoData[i].min_temp, &minTempF);
            strCelsiusToStrFahrenheit(meteoData[i].max_temp, &maxTempF); 
            bufferSize += sprintf(*jsonData + bufferSize, "{ \"date\" : \"%s\", \"city\" : \"%s\", \"maxTemp_F\" : \"%s\", \"minTemp_F\" : \"%s\", \"precipitations_mm\" : \"%s\" , \"cloudiness_%%\" : \"%s\"}", meteoData[i].date, meteoData[i].city, maxTempF, minTempF, meteoData[i].precipitations, meteoData[i].cloudiness);
            free(minTempF);
            free(maxTempF);

            // Agrega una "," si no es final de línea
            if (i < (meteoDataLength - 1)) {
                bufferSize += sprintf(*jsonData + bufferSize, ", ");
            }
        }
    }
    bufferSize += sprintf(*jsonData + bufferSize, " ]\n");

    return 0;
}