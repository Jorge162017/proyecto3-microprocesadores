/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* CC3086 Programación de microprocesadores
* Laboratorio 5
* 
* Autor: Jorge Lopez 221038
* --------------------------------------------------------*/
#include <iostream>
#include <pthread.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Sumatoria 1
// Función que calcula la sumatoria de los números naturales desde n hasta limite superior
long long calcularSumatoriaNaturales(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += i;
    }
    return sumatoria;
}

//Sumatoria 2
// Función que calcula la sumatoria de n^2 desde n hasta limite superior
long long calcularSumatoriaCuadrados(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += i * i;
    }
    return sumatoria;
}

// Barrrera para sincronizar los hilos antes de calcular el promedio
//pthread_barrier_t barreraPromedio;

//PROMEDIO
// Funcion que calcula el promedio de los resultados de las sumatorias
long long calcularPromedio(long long resultado1, long long resultado2) {
    return (resultado1 + resultado2) / 2;
}

// Estructura para pasar argumentos a la función de trabajo del hilo
struct ThreadArgs {
    long long nInicio;
    long long nFin;
    long long (*calcularSumatoria)(long long, long long);
    long long resultado;
};

// Mutex para proteger las variables compartidas
pthread_mutex_t mutexNaturales;
pthread_mutex_t mutexCuadrados;

// Función para inicializar los mutex
void inicializarMutex() {
    pthread_mutex_init(&mutexNaturales, nullptr);
    pthread_mutex_init(&mutexCuadrados, nullptr);
}

// Función de trabajo del hilo para calcular la sumatoria
void* calcularSumatoriaThread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->resultado = args->calcularSumatoria(args->nInicio, args->nFin);

    // Bloquear el mutex correspondiente antes de actualizar el resultado
    if (args->calcularSumatoria == calcularSumatoriaNaturales) {
        pthread_mutex_lock(&mutexNaturales);
    } else {
        pthread_mutex_lock(&mutexCuadrados);
    }

    // Actualizar el resultado y desbloquear el mutex
    args->resultado = args->calcularSumatoria(args->nInicio, args->nFin);
    if (args->calcularSumatoria == calcularSumatoriaNaturales) {
        pthread_mutex_unlock(&mutexNaturales);
    } else {
        pthread_mutex_unlock(&mutexCuadrados);
    }

    return nullptr;
}

int main() {
    // Se declaran las variables necesarias
    long long limiteInferior, limiteSuperior;
    int numHilos = 4; // Cambia 4 por el número de hilos que desees utilizar
    pthread_t* threadsNaturales = new pthread_t[numHilos];
    pthread_t* threadsCuadrados = new pthread_t[numHilos];
    ThreadArgs* threadArgsNaturales = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsCuadrados = new ThreadArgs[numHilos];

    // bienvenida
    printf("----------------------------------\n");
    printf("BIENVENIDO USUARIO!\n");
    printf("Este programa calcula las sumatorias en paralelo en un rango dado definido por ti.\n");
    printf("Por favor ingresa los datos que se te piden a continuación.\n");
    printf("----------------------------------\n");

    // Se piden los límites superior e inferior
    cout << "Ingrese el límite inferior: " << endl;
    cin >> limiteInferior;
    cout << "Ingrese el límite superior: " << endl;
    cin >> limiteSuperior;

    printf("\n");

    // Se inicia a calcular el tiempo de ejecución de la primera sumatoria
    auto startTimeSumatoria1 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de números naturales
    long long rangoNaturales = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsNaturales[i].nInicio = limiteInferior + i * rangoNaturales;
        threadArgsNaturales[i].nFin = threadArgsNaturales[i].nInicio + rangoNaturales - 1;
        threadArgsNaturales[i].calcularSumatoria = calcularSumatoriaNaturales;
        pthread_create(&threadsNaturales[i], nullptr, calcularSumatoriaThread, &threadArgsNaturales[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la primera sumatoria
    auto endTimeSumatoria1 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la segunda sumatoria
    auto startTimeSumatoria2 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de cuadrados
    long long rangoCuadrados = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsCuadrados[i].nInicio = limiteInferior + i * rangoCuadrados;
        threadArgsCuadrados[i].nFin = threadArgsCuadrados[i].nInicio + rangoCuadrados - 1;
        threadArgsCuadrados[i].calcularSumatoria = calcularSumatoriaCuadrados;
        pthread_create(&threadsCuadrados[i], nullptr, calcularSumatoriaThread, &threadArgsCuadrados[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la segunda sumatoria
    auto endTimeSumatoria2 = high_resolution_clock::now();

    // Inicializar la barrera para sincronizar los hilos antes de calcular el promedio
    //pthread_barrier_init(&barreraPromedio, nullptr, numHilos * 2);

    // Esperar a que los hilos de ambas sumatorias terminen
    for (int i = 0; i < numHilos; ++i) {
        pthread_join(threadsNaturales[i], nullptr);
        pthread_join(threadsCuadrados[i], nullptr);
    }

    // Atravesar la barrera para sincronizar los hilos antes de calcular el promedio
    //pthread_barrier_wait(&barreraPromedio);

    // Calcular el resultado final de ambas sumatorias
    long long resultadoNaturales = 0;
    long long resultadoCuadrados = 0;

    for (int i = 0; i < numHilos; ++i) {
        resultadoNaturales += threadArgsNaturales[i].resultado;
        resultadoCuadrados += threadArgsCuadrados[i].resultado;
    }

    // Calcular el promedio de los resultados de ambas sumatorias
    long long promedio = calcularPromedio(resultadoNaturales, resultadoCuadrados);

    // Imprimir los resultados de ambas sumatorias
    printf("---RESULTADOS DE LAS SUMATORIAS------------\n");
    cout << "Resultado de la sumatoria de números naturales: " << resultadoNaturales << endl;
    cout << "Resultado de la sumatoria de cuadrados: " << resultadoCuadrados << endl;
     printf("\n");

    // Imprimir los tiempos de ejecución de ambas sumatorias
    printf("---TIEMPOS DE EJECUCIÓN--------------------\n");
    auto durationSumatoria1 = duration_cast<microseconds>(endTimeSumatoria1 - startTimeSumatoria1);
    cout << "Tiempo de ejecución de la sumatoria de números naturales: " << durationSumatoria1.count() << " microsegundos" << endl;
    auto durationSumatoria2 = duration_cast<microseconds>(endTimeSumatoria2 - startTimeSumatoria2);
    cout << "Tiempo de ejecución de la sumatoria de cuadrados: " << durationSumatoria2.count() << " microsegundos" << endl;

    // Imprimir el promedio de los resultados 
    printf("\n");
    printf("---PROMEDIO DE LOS RESULTADOS--------------\n");
    cout << "Promedio de los resultados: " << promedio << endl;

    // Liberar memoria
    delete[] threadsNaturales;
    delete[] threadsCuadrados;
    delete[] threadArgsNaturales;
    delete[] threadArgsCuadrados;

    // Destruir la barrera
    //pthread_barrier_destroy(&barreraPromedio);

    // Destruir los mutex
    pthread_mutex_destroy(&mutexNaturales);
    pthread_mutex_destroy(&mutexCuadrados);

    return 0;
}