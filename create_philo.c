/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:23:56 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/03/18 17:35:11 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// para la funcion unsleep deberia pasarle 10000 microsegundos para 10 milisegundos
// Pasos para crear filósofos:
// Definir la estructura de filósofo: Cada filósofo tendrá un id, los tenedores que va a usar (uno a la izquierda y otro a la derecha), y un tiempo de última comida para simular si el filósofo muere por no haber comido en un tiempo determinado.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5

// Estructura para representar un filósofo
typedef struct s_philosopher {
    int id;                     // Identificador único para cada filósofo
    pthread_mutex_t *left_fork; // Tenedor de la izquierda
    pthread_mutex_t *right_fork;// Tenedor de la derecha
    long last_meal_time;       // Última vez que comió
} t_philosopher;

pthread_mutex_t forks[NUM_PHILOSOPHERS];   // Array de mutexes para los tenedores
pthread_t threads[NUM_PHILOSOPHERS];       // Hilos de filósofos
t_philosopher philosophers[NUM_PHILOSOPHERS]; // Array de filósofos

// Inicializar los filósofos: Cada filósofo necesita ser inicializado con su identificador (id), los tenedores que usará y el tiempo de su última comida.

void initialize_philosophers() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].id = i; // El id es el índice del filósofo
        philosophers[i].left_fork = &forks[i];  // El tenedor de la izquierda
        philosophers[i].right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS]; // El tenedor de la derecha
        philosophers[i].last_meal_time = 0; // Inicializamos el tiempo de la última comida
    }
}

//  Crear los hilos de filósofos: Luego, creas un hilo para cada filósofo, lo que permite que cada filósofo ejecute su propia rutina de pensar, comer, y esperar.

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (1) {
        // Pensar
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(1000000);  // Simula el tiempo de pensar

        // Tomar los tenedores
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);

        // Comer
        printf("Philosopher %d is eating\n", philo->id);
        philo->last_meal_time = get_current_time(); // Actualizamos la última comida
        usleep(1000000);  // Simula el tiempo de comer

        // Liberar los tenedores
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Verificar si el filósofo ha muerto
        if (get_current_time() - philo->last_meal_time > 5000) { // 5 segundos
            printf("Philosopher %d has died\n", philo->id);
            break;
        }
    }
    return NULL;
}

// Crear los hilos de los filósofos: Llamamos a pthread_create para crear un hilo por cada filósofo.

void create_philosophers() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
    }
}

// Esperar a que los hilos terminen: Después de crear los hilos, debes esperar a que todos terminen usando pthread_join.

void wait_for_philosophers() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }
}

// Inicializar mutexes y destruirlos: Antes de que los filósofos empiecen a comer, debes inicializar los mutexes que representarán los tenedores. Después de que todos los filósofos terminen, debes destruir los mutexes.

int main() {
    // Inicializar los mutexes para los tenedores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Inicializar filósofos
    initialize_philosophers();

    // Crear los hilos de los filósofos
    create_philosophers();

    // Esperar que los filósofos terminen
    wait_for_philosophers();

    // Destruir los mutexes de los tenedores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

/* Resumen:

    Definir los filósofos con una estructura que contiene su id, los tenedores, y el tiempo de última comida.
    Inicializar los filósofos, asignándoles tenedores y un id.
    Crear los hilos (filósofos) que ejecutarán su rutina de pensar, comer y liberar los tenedores.
    Esperar a que los hilos terminen usando pthread_join.
    Sincronizar el acceso a los tenedores mediante pthread_mutex_lock y pthread_mutex_unlock para evitar condiciones de carrera.
    Controlar el tiempo de ejecución para simular que los filósofos puedan morir si no comen durante un tiempo determinado.

	Este es el esquema básico para implementar el problema de los filósofos. Ten en cuenta que puedes agregar más detalles como el control
	de muertes, la cantidad de comida, la prioridad de los filósofos para evitar un deadlock, entre otros. */