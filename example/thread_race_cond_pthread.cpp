#include <iostream>         // std::cout, std::endl
#include <thread>           // std::thread
#include <vector>           // std::vector
#include <pthread.h>        // pthread_mutex_t, pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy

using namespace std;

#define NUM_THREADS 3
int shared_variable = 0;
pthread_mutex_t mutex;

void Increment()
{
    for (int i = 0; i < 3000000; i++)
    {
        pthread_mutex_lock(&mutex);
        shared_variable++;
        pthread_mutex_unlock(&mutex);
    }
}

int main (void)
{
    // Inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    // Cria um vetor de threads
    vector<thread> threads(NUM_THREADS);

    // Inicia todas as threads
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        threads[i] = thread(Increment);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        threads[i].join();
    }

    // Exibe o valor final da variável compartilhada
    cout << shared_variable << endl;

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
