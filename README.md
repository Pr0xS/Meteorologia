# Previsión meteorológica

Simple programa escrito en C que permite leer datos meteorológicos de un fichero .csv y mostrar la previsión meteorológica.

## Algunas características
Cuando los datos son cargados a memoria, estos datos son analizados y corregidos en caso de que sea necesario (corregir la notación decimal, eliminar posibles espacios en blanco delante o detrás de la palabra, etc)

Los datos son organizados en memoria de manera que las búsquedas sean optimas.
Para ello, se han organizado por ciudades, y para cada ciudad, los datos son organizados por fecha.
Para agilizar la búsqueda, se ha implementado una búsqueda binaria, con lo que consegimos una complejidad temporal de orden O(log n)

A la hora de interactuar con el usuario, se ha implementado una interfaz interactiva por consola, que guiará a usuario a través del programa. Algunas de estas opciones serán obligatorias, mientras que otras serán opcionales o contarán con valores por defecto. Estas últimas se podrán dejar en blanco.

Para finalizar, el código se ha estructurado en varios ficheros de acuerdo a la funcionalidad general de las funciones que contienen. De esta manera, se facilita el mantenimiento y la posibilidad de añadir nuevas funcionalidades al código

## Compilación
En la carpeta src se encuentra un archivo makefile que facilitará la compilación del programa

Simplemente ejecutando el siguiente comando deberíamos tener listo un programa llamado main listo para ejecutarse
```bash
make; make clean
```

## Uso
El programa generado por el makefile, nos generará un ejecutable llamado main
Ejecutaremos este programa con: 
```bash
./main
```
Y a continuación se nos irán requiriendo una serie de datos de manera interactiva, como el nombre del fichero de los datos, ciudad sobre la que realizar la búsqueda, o la fecha entre otros.

Algunos de estos campos serán opcionales y podremos dejarlos en blanco.
Al finalizar, se nos mostrará la información solicitada.

## Documentación
En la carpeta docs se encuentra la documentación generada por doxygen. Podemos encontrar 3 carpetas

* html
* latex
* pdf

En html se encuentra la versión web de la documentación, para verla simplemente deberemos abrir el archivo index.html en cualquier navegador.

En latex se encuentra los ficheros latex necesarios para crear la documentación en pdf.

En pdf se encuentra la versión pdf de la documentación
