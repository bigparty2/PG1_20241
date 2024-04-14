#include "mutex.hpp"

mutex::LamportMutex::LamportMutex(int num_threads)
{
    this->num_threads = num_threads;

    // Inicializa os vetores de flags e de números de ticket das threads
    for (int i = 0; i < num_threads; i++)
    {
        this->choosing.push_back(std::make_unique<std::atomic<bool>>(false));
        this->ticket.push_back(std::make_unique<std::atomic<int>>(0));
    }
}

mutex::LamportMutex::~LamportMutex(){}

void mutex::LamportMutex::lock(int thread_id)
{
    // Marca a thread atual como escolhendo um número
    this->choosing[thread_id]->store(true);

    // Escolhe o maior número de ticket dentre todas as threads
    int max_ticket = 0;
    for (int i = 0; i < this->num_threads; i++)
    {
        int current_ticket = this->ticket[i]->load();
        max_ticket = (current_ticket > max_ticket) ? current_ticket : max_ticket;
    }

    // Atribui um número de ticket maior que o maior número de ticket dentre todas as threads
    this->ticket[thread_id]->store(max_ticket + 1);

    // Marca a thread atual como não escolhendo um número
    this->choosing[thread_id]->store(false);

    // Aguarda até que todas as threads tenham escolhido um número
    for (int i = 0; i < this->num_threads; i++)
    {
        while (this->choosing[i]->load()) {}
        while ((this->ticket[i]->load() != 0) && 
              ((this->ticket[i]->load() < this->ticket[thread_id]->load()) || 
              ((this->ticket[i]->load() == this->ticket[thread_id]->load()) && 
              (i < thread_id)))) {}
    }
}

void mutex::LamportMutex::unlock(int thread_id)
{
    // Marca o número de ticket da thread atual como 0
    this->ticket[thread_id]->store(0);
}
