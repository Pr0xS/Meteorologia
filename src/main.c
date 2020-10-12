/**
 * @file main.c
 * @brief En este fichero se inicializa el programa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meteo.h"
#include "interfaces.h"
#include "helpers.h"


int main() {
    char filename[200];
    struct City * cities;
    struct Meteo * forecast;
    int num_cities;

    printf("[+] Introduce el nombre del fichero donde se encuentran los datos: ");
    getStringFromUserInput(filename, 200);



    num_cities = loadData(filename, &cities);

    if (num_cities == -1) {
        printf("[-] Se produjo un error al cargar los datos.\n");
        return 1;
    }


    // char date[100] = "2020/10/03";
    // char city[200] = "Madrid";
    // char unit = 'C';
    // int days = 5;

    char date[100];
    char city[200];
    char unit;
    int days, printJSON, saveJSON;

    int results = 0;
    
    int salir = 0;
    while (salir == 0) {
        if (interactiveMenu(city, date, &unit, &days, &printJSON, &saveJSON) == -1) {
            printf("Error al obtener los datos \n");
            exit(1);
        }

        results = getForecast(cities, num_cities, &forecast, city, date, days);

        if (results > 0) {
            showForecast(forecast, results, unit);
            if (results < days) {
                printf("[*] Solo se han encontrado datos para %i días de los %i solicitados\n\n", results, days);
            } else {
                printf("\n\n");
            }

            if (printJSON == 1 || saveJSON == 1) {
                char * jsonData;
                meteoDataToJSON(forecast, results, &jsonData, unit);

                if (printJSON == 1) {
                    printf("[+] Mostrado datos en formato JSON\n\n");
                    printf("%s\n", jsonData);
                }
                if (saveJSON == 1) {
                    char name[50];
                    sprintf(name, "data_%s(%s).json", city, date);
                    replace(name, '/', '-');
                    int error = storeToFile(name, jsonData);
                    if (error) {
                        printf("[-] Se produjo un error al guardar el fichero \"%s\"\n", name);
                    } else {
                        printf("[+] Datos guardados con éxito en \"%s\"\n", name);
                    }
                }
                free(jsonData);
            }

        } else if (results == -1) {
            printf("\n[-] La ciudad \"%s\" no ha sido encontrada\n", city);
        } else if (results == -2) {
            printf("\n[-] No se han encontrado resultados para \"%s\" en la fecha \"%s\".\n", city, date);
        } else if (results == -3) {
            printf("\n[-] Se ha producido un error al solicitar el pronóstico meteorológico\n");
        }

        // Liberamos memoria de forecast
        free(forecast);
        forecast = NULL;




        while (1) {
            printf("[+] Nueva búsqueda (s/n): ");
            int status;
            char answer[3];
            status = getStringFromUserInput(answer, 3);

            if (status == 0) {
                // No se ha introducido nada
                printf("[-] Introduzca S (nueva búsqueda) o N (salir)\n");
            } else if (answer[0] == 'S' || answer[0] == 's'){
                salir = 0;
                break;
            } else if (answer[0] == 'N' || answer[0] == 'n') {
                salir = 1;
                break;
            } else {
                printf("[-] Introduzca S (nueva búsqueda) o N.\n");
            }
        }


    }


    // Liberamos memoria de nuestra estructura de datos cities
    for (int i = 0; i < num_cities; i++) {
        free(cities[i].meteoData_array);
    }
    free(cities);
    cities = NULL;
    return (0);
}