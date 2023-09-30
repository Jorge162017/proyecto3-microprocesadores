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
#include <math.h>

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

// Sumatoria 3
// Funcion que calcula la sumatoria de n/2 desde n hasta limite superior
long long calcularSumatoriaDivididos(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += i / 2;
    }
    return sumatoria;
}

// Sumatoria 4
// Funcion que calcula la sumatoria de 1/n^2 desde n hasta limite superior
long long calcularSumatoriaInversos(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += 1 / (i * i);
    }
    return sumatoria;
}

// Sumatoria 5
// Funcion que calcula la sumatoria la raiz cuadrada de n desde n hasta limite superior
long long calcularSumatoriaRaiz(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += sqrt(i);
    }
    return sumatoria;
}

// Sumatoria 6
// Funcion que calcula la sumatoria de 1/2*n desde n hasta limite superior
long long calcularSumatoriaDivididos2(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += 1 / (2 * i);
    }
    return sumatoria;
}

// Sumatoria 7
// Funcion que calcula la sumatoria de log(n) desde n hasta limite superior
long long calcularSumatoriaLog(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += log(i);
    }
    return sumatoria;
}

// Sumatoria 8
// Funcion que calcula la sumatoria de n^3 desde n hasta limite superior
long long calcularSumatoriaCubos(long long n, long long limiteSuperior) {
    long long sumatoria = 0;
    for (long long i = n; i <= limiteSuperior; ++i) {
        sumatoria += i * i * i;
    }
    return sumatoria;
}

// Barrrera para sincronizar los hilos antes de calcular el promedio
//pthread_barrier_t barreraPromedio;

//PROMEDIO
// Funcion que calcula el promedio de los resultados de las sumatorias
long long calcularPromedio(long long resultado1, long long resultado2, long long resultado3, long long resultado4, long long resultado5, long long resultado6, long long resultado7, long long resultado8) {
    return (resultado1 + resultado2 + resultado3 + resultado4 + resultado5 + resultado6 + resultado7 + resultado8) / 8;
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
pthread_mutex_t mutexDivididos;
pthread_mutex_t mutexInversos;
pthread_mutex_t mutexRaiz;
pthread_mutex_t mutexDivididos2;
pthread_mutex_t mutexLog;
pthread_mutex_t mutexCubos;

// Función para inicializar los mutex
void inicializarMutex() {
    pthread_mutex_init(&mutexNaturales, nullptr);
    pthread_mutex_init(&mutexCuadrados, nullptr);
    pthread_mutex_init(&mutexDivididos, nullptr);
    pthread_mutex_init(&mutexInversos, nullptr);
    pthread_mutex_init(&mutexRaiz, nullptr);
    pthread_mutex_init(&mutexDivididos2, nullptr);
    pthread_mutex_init(&mutexLog, nullptr);
    pthread_mutex_init(&mutexCubos, nullptr);
}

// Función de trabajo del hilo para calcular la sumatoria
void* calcularSumatoriaThread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->resultado = args->calcularSumatoria(args->nInicio, args->nFin);

    // Bloquear el mutex correspondiente antes de actualizar el resultado
    if (args->calcularSumatoria == calcularSumatoriaNaturales) {
        pthread_mutex_lock(&mutexNaturales);
    } else if (args->calcularSumatoria == calcularSumatoriaCuadrados) {
        pthread_mutex_lock(&mutexCuadrados);
    } else if (args->calcularSumatoria == calcularSumatoriaDivididos) {
        pthread_mutex_lock(&mutexDivididos);
    } else if (args->calcularSumatoria == calcularSumatoriaInversos) {
        pthread_mutex_lock(&mutexInversos);
    } else if (args->calcularSumatoria == calcularSumatoriaRaiz) {
        pthread_mutex_lock(&mutexRaiz);
    } else if (args->calcularSumatoria == calcularSumatoriaDivididos2) {
        pthread_mutex_lock(&mutexDivididos2);
    } else if (args->calcularSumatoria == calcularSumatoriaLog) {
        pthread_mutex_lock(&mutexLog);
    } else if (args->calcularSumatoria == calcularSumatoriaCubos) {
        pthread_mutex_lock(&mutexCubos);
    }
   


    // Actualizar el resultado y desbloquear el mutex
    args->resultado = args->calcularSumatoria(args->nInicio, args->nFin);
    if (args->calcularSumatoria == calcularSumatoriaNaturales) {
        pthread_mutex_unlock(&mutexNaturales);
    } else if (args->calcularSumatoria == calcularSumatoriaCuadrados) {
        pthread_mutex_unlock(&mutexCuadrados);
    } else if (args->calcularSumatoria == calcularSumatoriaDivididos) {
        pthread_mutex_unlock(&mutexDivididos);
    } else if (args->calcularSumatoria == calcularSumatoriaInversos) {
        pthread_mutex_unlock(&mutexInversos);
    } else if (args->calcularSumatoria == calcularSumatoriaRaiz) {
        pthread_mutex_unlock(&mutexRaiz);
    } else if (args->calcularSumatoria == calcularSumatoriaDivididos2) {
        pthread_mutex_unlock(&mutexDivididos2);
    } else if (args->calcularSumatoria == calcularSumatoriaLog) {
        pthread_mutex_unlock(&mutexLog);
    } else if (args->calcularSumatoria == calcularSumatoriaCubos) {
        pthread_mutex_unlock(&mutexCubos);
    }
        return nullptr;
    }

int main() {
    // Se declaran las variables necesarias
    long long limiteInferior, limiteSuperior;
    int numHilos = 10; // Cambia 4 por el número de hilos que desees utilizar
    pthread_t* threadsNaturales = new pthread_t[numHilos];
    pthread_t* threadsCuadrados = new pthread_t[numHilos];
    pthread_t* threadsDivididos = new pthread_t[numHilos];
    pthread_t* threadsInversos = new pthread_t[numHilos];
    pthread_t* threadsRaiz = new pthread_t[numHilos];
    pthread_t* threadsLog = new pthread_t[numHilos];
    pthread_t* threadsDivididos2 = new pthread_t[numHilos];
    pthread_t* threadsCubos = new pthread_t[numHilos];
    ThreadArgs* threadArgsNaturales = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsCuadrados = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsDivididos = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsInversos = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsRaiz = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsDivididos2 = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsLog = new ThreadArgs[numHilos];
    ThreadArgs* threadArgsCubos = new ThreadArgs[numHilos];

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

    // Se inicia a calcular el tiempo de ejecución de la tercera sumatoria
    auto startTimeSumatoria3 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoDivididos = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsDivididos[i].nInicio = limiteInferior + i * rangoDivididos;
        threadArgsDivididos[i].nFin = threadArgsDivididos[i].nInicio + rangoDivididos - 1;
        threadArgsDivididos[i].calcularSumatoria = calcularSumatoriaDivididos;
        pthread_create(&threadsDivididos[i], nullptr, calcularSumatoriaThread, &threadArgsDivididos[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la tercera sumatoria
    auto endTimeSumatoria3 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la cuarta sumatoria
    auto startTimeSumatoria4 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoInversos = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsInversos[i].nInicio = limiteInferior + i * rangoInversos;
        threadArgsInversos[i].nFin = threadArgsInversos[i].nInicio + rangoInversos - 1;
        threadArgsInversos[i].calcularSumatoria = calcularSumatoriaInversos;
        pthread_create(&threadsInversos[i], nullptr, calcularSumatoriaThread, &threadArgsInversos[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la cuarta sumatoria
    auto endTimeSumatoria4 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la quinta sumatoria
    auto startTimeSumatoria5 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoRaiz = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsRaiz[i].nInicio = limiteInferior + i * rangoRaiz;
        threadArgsRaiz[i].nFin = threadArgsRaiz[i].nInicio + rangoRaiz - 1;
        threadArgsRaiz[i].calcularSumatoria = calcularSumatoriaRaiz;
        pthread_create(&threadsRaiz[i], nullptr, calcularSumatoriaThread, &threadArgsRaiz[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la quinta sumatoria
    auto endTimeSumatoria5 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la sexta sumatoria
    auto startTimeSumatoria6 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoDivididos2 = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsDivididos2[i].nInicio = limiteInferior + i * rangoDivididos2;
        threadArgsDivididos2[i].nFin = threadArgsDivididos2[i].nInicio + rangoDivididos2 - 1;
        threadArgsDivididos2[i].calcularSumatoria = calcularSumatoriaDivididos2;
        pthread_create(&threadsDivididos2[i], nullptr, calcularSumatoriaThread, &threadArgsDivididos2[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la sexta sumatoria
    auto endTimeSumatoria6 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la septima sumatoria
    auto startTimeSumatoria7 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoLog = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsLog[i].nInicio = limiteInferior + i * rangoLog;
        threadArgsLog[i].nFin = threadArgsLog[i].nInicio + rangoLog - 1;
        threadArgsLog[i].calcularSumatoria = calcularSumatoriaLog;
        pthread_create(&threadsLog[i], nullptr, calcularSumatoriaThread, &threadArgsLog[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la septima sumatoria
    auto endTimeSumatoria7 = high_resolution_clock::now();

    // Se inicia a calcular el tiempo de ejecución de la octava sumatoria
    auto startTimeSumatoria8 = high_resolution_clock::now();
    // Dividir el trabajo entre los hilos para la sumatoria de divididos
    long long rangoCubos = (limiteSuperior - limiteInferior + 1) / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        threadArgsCubos[i].nInicio = limiteInferior + i * rangoCubos;
        threadArgsCubos[i].nFin = threadArgsCubos[i].nInicio + rangoCubos - 1;
        threadArgsCubos[i].calcularSumatoria = calcularSumatoriaCubos;
        pthread_create(&threadsCubos[i], nullptr, calcularSumatoriaThread, &threadArgsCubos[i]);
    }
    // Se terminan de calcular los tiempos de ejecución de la octava sumatoria  
    auto endTimeSumatoria8 = high_resolution_clock::now();

    // Inicializar la barrera para sincronizar los hilos antes de calcular el promedio
    //pthread_barrier_init(&barreraPromedio, nullptr, numHilos * 2);

    // Esperar a que los hilos de ambas sumatorias terminen
    for (int i = 0; i < numHilos; ++i) {
        pthread_join(threadsNaturales[i], nullptr);
        pthread_join(threadsCuadrados[i], nullptr);
        pthread_join(threadsDivididos[i], nullptr);
        pthread_join(threadsInversos[i], nullptr);
        pthread_join(threadsRaiz[i], nullptr);
        pthread_join(threadsDivididos2[i], nullptr);
        pthread_join(threadsLog[i], nullptr);
        pthread_join(threadsCubos[i], nullptr);
    }

    // Atravesar la barrera para sincronizar los hilos antes de calcular el promedio
    //pthread_barrier_wait(&barreraPromedio);

    // Calcular el resultado final de ambas sumatorias
    long long resultadoNaturales = 0;
    long long resultadoCuadrados = 0;
    long long resultadoDivididos = 0;
    long long resultadoInversos = 0;
    long long resultadoRaiz = 0;
    long long resultadoDivididos2 = 0;
    long long resultadoLog = 0;
    long long resultadoCubos = 0;

    for (int i = 0; i < numHilos; ++i) {
        resultadoNaturales += threadArgsNaturales[i].resultado;
        resultadoCuadrados += threadArgsCuadrados[i].resultado;
        resultadoDivididos += threadArgsDivididos[i].resultado;
        resultadoInversos += threadArgsInversos[i].resultado;
        resultadoRaiz += threadArgsRaiz[i].resultado;
        resultadoDivididos2 += threadArgsDivididos2[i].resultado;
        resultadoLog += threadArgsLog[i].resultado;
        resultadoCubos += threadArgsCubos[i].resultado;
    }

    // Calcular el promedio de los resultados de ambas sumatorias
    long long promedio = calcularPromedio(resultadoNaturales, resultadoCuadrados, resultadoDivididos, resultadoInversos, resultadoRaiz, resultadoDivididos2, resultadoLog, resultadoCubos);

    // Imprimir los resultados de ambas sumatorias
    printf("---RESULTADOS DE LAS SUMATORIAS------------\n");
    cout << "Resultado de la sumatoria de números naturales: " << resultadoNaturales << endl;
    cout << "Resultado de la sumatoria de cuadrados: " << resultadoCuadrados << endl;
    cout << "Resultado de la sumatoria de divididos: " << resultadoDivididos << endl;
    cout << "Resultado de la sumatoria de inversos: " << resultadoInversos << endl;
    cout << "Resultado de la sumatoria de raiz: " << resultadoRaiz << endl;
    cout << "Resultado de la sumatoria de divididos2: " << resultadoDivididos2 << endl;
    cout << "Resultado de la sumatoria de log: " << resultadoLog << endl;
    cout << "Resultado de la sumatoria de cubos: " << resultadoCubos << endl;
     printf("\n");

    // Imprimir los tiempos de ejecución de ambas sumatorias
    printf("---TIEMPOS DE EJECUCIÓN--------------------\n");
    auto durationSumatoria1 = duration_cast<microseconds>(endTimeSumatoria1 - startTimeSumatoria1);
    cout << "Tiempo de ejecución de la sumatoria de números naturales: " << durationSumatoria1.count() << " microsegundos" << endl;
    auto durationSumatoria2 = duration_cast<microseconds>(endTimeSumatoria2 - startTimeSumatoria2);
    cout << "Tiempo de ejecución de la sumatoria de cuadrados: " << durationSumatoria2.count() << " microsegundos" << endl;
    auto durationSumatoria3 = duration_cast<microseconds>(endTimeSumatoria3 - startTimeSumatoria3);
    cout << "Tiempo de ejecución de la sumatoria de divididos: " << durationSumatoria3.count() << " microsegundos" << endl;
    auto durationSumatoria4 = duration_cast<microseconds>(endTimeSumatoria4 - startTimeSumatoria4);
    cout << "Tiempo de ejecución de la sumatoria de inversos: " << durationSumatoria4.count() << " microsegundos" << endl;
    auto durationSumatoria5 = duration_cast<microseconds>(endTimeSumatoria5 - startTimeSumatoria5);
    cout << "Tiempo de ejecución de la sumatoria de raiz: " << durationSumatoria5.count() << " microsegundos" << endl;
    auto durationSumatoria6 = duration_cast<microseconds>(endTimeSumatoria6 - startTimeSumatoria6);
    cout << "Tiempo de ejecución de la sumatoria de divididos2: " << durationSumatoria6.count() << " microsegundos" << endl;
    auto durationSumatoria7 = duration_cast<microseconds>(endTimeSumatoria7 - startTimeSumatoria7);
    cout << "Tiempo de ejecución de la sumatoria de log: " << durationSumatoria7.count() << " microsegundos" << endl;
    auto durationSumatoria8 = duration_cast<microseconds>(endTimeSumatoria8 - startTimeSumatoria8);
    cout << "Tiempo de ejecución de la sumatoria de cubos: " << durationSumatoria8.count() << " microsegundos" << endl;

    // Imprimir el promedio de los resultados 
    printf("\n");
    printf("---PROMEDIO DE LOS RESULTADOS--------------\n");
    cout << "Promedio de los resultados: " << promedio << endl;

    // Liberar memoria
    delete[] threadsNaturales;
    delete[] threadsCuadrados;
    delete[] threadsDivididos;
    delete[] threadArgsNaturales;
    delete[] threadArgsCuadrados;
    delete[] threadArgsDivididos;
    delete[] threadsInversos;
    delete[] threadsRaiz;
    delete[] threadsDivididos2;
    delete[] threadsLog;
    delete[] threadsCubos;

    // Destruir la barrera
    //pthread_barrier_destroy(&barreraPromedio);

    // Destruir los mutex
    pthread_mutex_destroy(&mutexNaturales);
    pthread_mutex_destroy(&mutexCuadrados);
    pthread_mutex_destroy(&mutexDivididos);
    pthread_mutex_destroy(&mutexInversos);
    pthread_mutex_destroy(&mutexRaiz);
    pthread_mutex_destroy(&mutexDivididos2);
    pthread_mutex_destroy(&mutexLog);
    pthread_mutex_destroy(&mutexCubos);

    return 0;
}
