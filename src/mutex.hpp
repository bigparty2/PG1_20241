#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <vector>   // uso de vetores c++
#include <atomic>   // uso de variáveis atômicas (garantia de atomicidade em operações de leitura e escrita)
#include <memory>   // uso de ponteiros inteligentes

namespace mutex
{
    /**
     * @brief Classe que implementa um mutex de Lamport.
     * 
     * Esta classe implementa um mutex de Lamport, que é um algoritmo de exclusão mútua que permite
     * que várias threads acessem um recurso compartilhado de forma mutuamente exclusiva.
     */
    class LamportMutex
    {
    public:

        /**
         * @brief Construtor da classe LamportMutex.
         * 
         * @param num_threads Número de threads que podem acessar o recurso compartilhado.
         */
        LamportMutex(int num_threads);

        ~LamportMutex();
        
        /**
         * @brief Adquire o bloqueio do mutex de Lamport para a thread especificada.
         * 
         * @param thread_id O ID da thread que deseja adquirir o bloqueio do mutex.
         */
        void lock(int thread_id);
        
        /**
         * @brief Libera o bloqueio do mutex de Lamport para a thread especificada.
         * 
         * @param thread_id O ID da thread que deseja liberar o bloqueio do mutex.
         */
        void unlock(int thread_id);
    
    private:

        /// @brief Vetor de flags que indicam se a thread está escolhendo um número.
        std::vector<std::unique_ptr<std::atomic<bool>>> choosing;
    
        /// @brief Vetor de números de ticket das threads.
        std::vector<std::unique_ptr<std::atomic<int>>> ticket;

        /// @brief Número de threads que podem acessar o recurso compartilhado.
        int num_threads;
    };
}

#endif // MUTEX_HPP