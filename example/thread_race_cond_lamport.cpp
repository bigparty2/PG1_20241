
#include <iostream>         // std::cout, std::endl
#include <thread>           // std::thread
#include "../src/mutex.hpp" // mutex::LamportMutex

using namespace std;
using namespace mutex;

#define NUM_THREADS 3
LamportMutex lamportMutex(NUM_THREADS);
int shared_variable = 0;

int Increment(int thread_id)
{
    for (int i = 0; i < 3000000; i++)
    {
        lamportMutex.lock(thread_id);
        shared_variable++;
        lamportMutex.unlock(thread_id);
    }

    return 0;
}

int main (void)
{
    // Cria um vetor de threads
    vector<thread> threads(NUM_THREADS);

    // Inicia todas as threads
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        threads[i] = thread(Increment, i);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        threads[i].join();
    }

    // Exibe o valor final da variável compartilhada
    cout << shared_variable << endl;

    return EXIT_SUCCESS;
}