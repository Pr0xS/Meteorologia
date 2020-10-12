/**
 * @file interfaces.c
 * @brief En este fichero están definidas las funciones declaradas en interfaces.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"

#include "meteo.h"
#include "helpers.h"


int interactiveMenu(char * city, char * date, char * unit, int * days, int * printJSON, int * saveJSON) {
    int status;

    system("clear");

    printf("***************************************************************\n");
    printf("*                   SERVICIO METEOROLÓGICO                    *\n");
    printf("***************************************************************\n\n");
    printf("Rellena la siguiente información\n");
    printf("Si no se introduce nada, se seleccionará la opción por defecto.\n");
    printf("Los campos predecedidos con (*) son obligatorios\n\n");
    

    // Solicitamos datos de la ciudad
    printf("[+] Introduce la ciudad sobre la que realizar la búsqueda.\n");
    status = 0;
    while (status == 0) {
        printf("    (*) Ciudad: ");
        status = getStringFromUserInput(city, 200);
        if (status == 0) {
            printf("[-] El campo Ciudad, no puede estar vacío\n");
        }
        if (status == -1) {
            return -1;
        }
    }
    
    // Solicitamos datos de la fecha
    printf("\n[+] Introduce la fecha sobre la que realizar la búsqueda. Formato (AAAA/MM/DD)\n");
    status = 0;
    while (status == 0) {
        printf("    (*) Fecha: ");
        status = getStringFromUserInput(date, 100);
        if (status == 0) {
            printf("[-] El campo Fecha, no puede estar vacío\n");
        }
        if (status == -1) {
            return -1;
        }
    }

    // Solicitamos la unidad de medida
    printf("\n[+] Introduzca la únidad de Medida: C para Celsius, F para Fahrenheit.\n");
    printf("    Si se deja en blanco, se utilizarán grados Celsius.\n");
    status = 0;
    while (status == 0) {
        char aux[10];

        printf("    Unidad: ");
        status = getStringFromUserInput(aux, 10);

        if (status == 0) {
            *unit = 'C';
            printf("[?] Se usarán grados Celsius\n");
            break;
        }
        if (status > 1) {
            printf("[-] Introduce únicamente una letra C para Celsius, F para Fahrenheit\n");
            status = 0;
        } 
        
        if (status == -1) {
            return -1;
        }

        if (status == 1) {
            if (aux[0] == 'C' || aux[0] == 'c') {
                *unit = 'C';
                break;
            } else if (aux[0] == 'F' || aux[0] == 'f') {
                *unit = 'F';
                break;
            } else {
                printf("[-] La únicas opciones válidas son C para Celsius o F par Fahrenheit\n");
                status = 0;
            }
        }
        
    }

    // Solicitamos el número de dias para la previsión meteorológica
    printf("\n[+] Introduzca cuando días de previsión meteorológica quiere obtener.\n");
    printf("    Si no se introduce nada, se utilizará el valor por defecto (5).\n");
    status = 0;
    while (status == 0) {
        printf("    Días: ");
        status = getIntFromUserInput(days);
        if (status == -1) {
            *days = 5;
            printf("[?] Se buscará el pronóstico de los 5 próximos días\n");
            break;
        }
        status = 1;
    }


    // Preguntamos si se desea mostar el resultado en fomato JSON
    printf("\n[+] ¿Mostrar los datos obtenidos en JSON?\n");
    printf("    Si no se introduce nada, no se mostrarán.\n");
    status = 0;
    while (status == 0) {
        printf("    Si o No: ");
        char answer[3];
        status = getStringFromUserInput(answer, 3);

        if (status == 0) {
            // No se ha introducido nada
            status = 1;
            *printJSON = 0;
            printf("[?] No se mostrará en formato JSON\n");
            break;
        } else if (answer[0] == 'S' || answer[0] == 's'){
            status = 1;
            *printJSON = 1;
            break;
        } else if (answer[0] == 'N' || answer[0] == 'n') {
            status = 1;
            *printJSON = 0;
            break;
        } else {
            printf("[-] Introduza Si o No. Si no introduce nada, no se mostrará por pantalla en formato JSON\n");
        }
    }


    // Preguntamos si se desea guardar el resultado en JSON
    printf("\n[+] ¿Guardar los datos obtenidos en un fichero .json?\n");
    printf("    Si no se introduce nada, SI se guararán en un fichero llamado \"data.json\".\n");
    status = 0;
    while (status == 0) {
        printf("    Si o No: ");
        char answer[3];
        status = getStringFromUserInput(answer, 3);

        if (status == 0) {
            // No se ha introducido nada
            status = 1;
            *saveJSON = 1;
            printf("[?] No se mostrará en formato JSON\n");
            break;
        } else if (answer[0] == 'S' || answer[0] == 's'){
            status = 1;
            *saveJSON = 1;
            break;
        } else if (answer[0] == 'N' || answer[0] == 'n') {
            status = 1;
            *saveJSON = 0;
            break;
        } else {
            printf("[-] Introduza Si o No. Si no se introduce nada, SI se guararán en un fichero llamado \"data_ciudad(fecha).json\".\n");

        }
    }

    printf("\n");
    
    return 0;
}


int showForecast(struct Meteo * forecast, int n_data, char unit) {
    system("clear");

    printf("********************************************************************\n");
    printf("*                      REPORTE METEOROLÓGICO                       *\n");
    printf("********************************************************************\n\n");
    printf(" Ciudad: %s\n", forecast[0].city);
    printf(" ------------------------------------------------------------------\n");
    printf("|   Fecha     T. Mínimas (%c)   T.Máximas (%c)   Precipiaciones (mm) |\n", unit, unit);
    printf(" ------------------------------------------------------------------\n");
    for (int i = 0; i < n_data; i++) {
        if (unit == 'C') {
            printf("| %-15s %-15s %-19s %-12s |\n", forecast[i].date, forecast[i].min_temp, forecast[i].max_temp, forecast[i].precipitations);
        } else {
            char * minFah, * maxFah;

            strCelsiusToStrFahrenheit(forecast[i].min_temp, &minFah);
            strCelsiusToStrFahrenheit(forecast[i].max_temp, &maxFah);

            printf("| %-15s %-15s %-19s %-12s |\n", forecast[i].date, minFah, maxFah, forecast[i].precipitations);

            free(minFah);
            free(maxFah);
        }
    }
    printf(" ------------------------------------------------------------------\n");

    return 0;
}