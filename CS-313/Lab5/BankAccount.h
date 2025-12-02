#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class BankAccount
{
        private:
                int64_t    balance;
                std::mutex m;

        public:
                BankAccount();
                void perform_transaction(const int64_t amount);

                // Interface function to perform threadsafe transactions
                // You will need to implement the transaction_threadsafe() function...
                // using mutexes to ensure safe concurrency
                void perform_threadsafe_transaction(const int64_t amount);
                void print_balance() const;
};

#endif
