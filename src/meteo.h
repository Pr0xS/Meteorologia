/**
 * @file meteo.h
 * @brief En este fichero están declaradas aquellas funciones que están relacionadas con el manejo y procesamiento
 * de los datos relacionados con la meteorología
 */

#ifndef METEO_H
#define METEO_H


/**
 * @struct City
 * @brief Estructura de datos que contiene la informacíon de la ciudad almacenada
 */
struct City {

    char city[100];                     /**< Nombre de la ciudad */
    int n_meteoData_entries;            /**< Número de entradas meteorológicas almacenadas para esta ciudad */
    int memory_reserved;                /**< Número de espacio reservado para entradas meteorológicas */
    struct Meteo * meteoData_array;     /**< Array con la infomación meteorológica para la ciudad */
};


/**
 * @struct Meteo
 * @brief Estructura de datos que continen la información meteorilógica de una ciudad en una fecha determinada
 */
struct Meteo {

    char date[50];                      /**< Fecha de la entrada meteorológica */
    char city[100];                     /**< Nombre de la ciudad de la entrada meteorológica */
    char max_temp[50];                  /**< Temperatura máxima de la entrada meteorológica */
    char min_temp[50];                  /**< Temperatura mínima de la entrada meteorológica */
    char precipitations[50];            /**< Precipitaciones de la entrada meteorológica */
    char cloudiness[50];                /**< Nubosidad de lea entrada meteorológica */
};


/**
 * @fn void printMeteoEntry(struct Meteo meteoData);
 * @brief La funcion printMeteoEntry() muestra por pantalla la información de la entrada meteorológica recibida
 * @param meteoData Se trata de una estructura de datos de tipo Meteo la cual contiene la información a mostrar por 
 * pantalla 
 */
void printMeteoEntry(struct Meteo meteoData);


/**
 * @fn int loadData(const char * filename, struct City ** cities);
 * @brief La función loadData() carga datos desde un fichero de texto en formato csv a un array de ciudades de tipo 
 * City (struct City *). Para cada entrada de este array de ciudades, se encuantrasn los datos meteorológicos 
 * correspondientes a cada ciudad. Las ciudades son ordenadas por orden Alfabético para facilitar su búsqueda.
 * @param filename Se trata de un string (char *) que contiene el nombre del fichero de texto a cargar.
 * @param cities Se trata de un puntero a un array de estructuras de tipo City (struct City **) en el que se van a 
 * almacenar los datos cargados por ciudades
 * @return La función loadData() devuelve el número de elementos cargados si tiene éxito. En caso de error devolverá
 * -1.
 * @warning Es necesario liberar la memoria reservada en la función loadData() del parametro cities. Para ello 
 * liberaremos la información para cada entrada meteorológica para cada ciudad y posteriormente liberaremos la memoria
 * reservada para cada ciudad.
 */
int loadData(const char * filename, struct City ** cities);


/**
 * @fn struct Meteo customMeteoDataParser(char * line);
 * @brief La función customMeteoDataParser() recibe una string con los datos Meteorológicos en formato csv y
 * los convierte a una estructura de datos de tipo struct Meteo.
 * @param line Se trata de un string (char *) que contiene la string con los datos que se quieren cargar.
 * @return La función customMeteoDataParser() devuelve una estructura de datos de tipo Meteo (struct Meteo) con
 * los datos cargados del string line
 */
struct Meteo customMeteoDataParser(char * line);


/**
 * @fn int binarySearchCities(char * city, struct City * cities, int numCities);
 * @brief La función binarySearchCities() realiza una busqueda binaria en el array de ciudades 
 * @param city Se trata de un string (char *) que contiene el nombre de la ciudad a buscar
 * @param cities Se trata de un array de estructuras de tipo City (struct City *) que contiene las
 * cidudades sobre las que se realizará la busqueda
 * @param numCities Se trata de un entero con el número de ciudades almacenadas
 * @return La función binarySearchCities devuelve la posición en el array de la ciudad si la ciudad es 
 * encontrada. Si no se ha encontrado devolverá -1.
 */
int binarySearchCities(char * city, struct City * cities, int numCities);


/**
 * @fn int binarySearchDates(char * date, struct Meteo * meteoData, int numDataEntries);
 * @brief La función binarySearchCities() realiza una busqueda binaria en el array de ciudades 
 * @param city Se trata de un puntero a una string (char *) que contiene el nombre de la ciudad a buscar
 * @param cities Se trata de un array de estructuras de tipo City (struct City *) que contiene las
 * cidudades sobre las que se realizará la busqueda
 * @param numCities Se trata de un entero con el número de ciudades almacenadas
 * @return La función binarySearchCities devuelve la posición en el array de la ciudad si la ciudad es 
 * encontrada. Si no se ha encontrado devolverá -1.
 */
int binarySearchDates(char * date, struct Meteo * meteoData, int numDataEntries);


/**
 * @fn int getForecast(struct City *, char * city, char date *, int days);
 * @brief La función getForecast() realiza una busqueda con los parametros proporcionados y devuelve
 * los datos meteorológicos con la previsión metorológica de los proximos días.
 * @param cities Se trata de un array de estructuras de tipo City (struct City *) que contine la infomación
 * meteorologíca por ciudades.
 * @param numCities Se trata de un entero que contiene el número de ciudades almacenado
 * @param forecast Se trata de un array de estructuras de tipo Meteo (struct Meteo *) sobre el que se guardará
 * la previsión meteorológica de la búsqueda realizada.
 * @param city Se trata de un string (char *) que contiene el nombre de la ciudad sobre la que
 * se realizará la busqueda.
 * @param date Se trata de un string (char *) que contiene la fecha sobre la que realizar la
 * búsqueda.
 * @param days Se trata de un entero que contiene el número de días sobre de los que se quiere la previsión
 * meteorológica.
 * @return La función getForecast devuelve un número entero. Si la operación se ha realizado con éxito, devoverá
 * un número entero positivo correspondiente al número de resultados devueltos. Si no se ha encontrado la ciudad 
 * que se buscaba, devolverá un -1. Si no se ha encontrado información meteorológica para la fecha indicada,
 * devolverá un -2. En caso de cualquier otro error, devoverá -3.
 * @warning Es necesario liberar la memoria reservada por la funcion getForecast() del parametro forecast. Para ello
 * liberaremos la memoria del propio array forecast.
 */
int getForecast(struct City * cities, int numCities, struct Meteo ** forecast, char * city, char * date, int days);


/**
 * @fn int meteoDataToJSON(struct Meteo * meteoData, int meteoDataLength, char * jsonData);
 * @brief La función meteoDataToJSON() convierte la información meteorológica proporcionada en el formato de 
 * datos JSON.
 * @param meteoData Se trata de array de estructuras de tipo Meto (struct * Meteo) que contiene la información
 * meteorológica que se desea convertir a JSON.
 * @param meteoDataLength Se trata de un entero que contiene el número de entradas meterológicas que se encuentran
 * en el array meteoData
 * @param jsonData Se trata de un puntero a un string (char **) que contrendrá la información en fomrmato JSON
 * @return La función meteoDataToJSON() devueve un entero con valor 0 en caso de éxtio y un -1 en caso de producirse
 * un error.
 * @param unit Se trata de un caracter (char) que indica la unidad en la que se han de guardar las temperaturas, C para
 * Celsius o F para Fahrenheit.
 * @warning En necesaroi liberar la memoria reservada por la función meteoDataToJSON del parametro jsonDATA. Para ello
 * liberaremos la memoria de la propia valirable jsonData.
 */
int meteoDataToJSON(struct Meteo * meteoData, int meteoDataLength, char ** jsonData, char unit);


#endif /* METEO_H */