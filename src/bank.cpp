#include <cstdio>
#include <fstream>
#include <numeric>
#include <stdlib.h>

#include "bank.h"
#include "example.h"

#define AS_TYPE(Type, Obj) reinterpret_cast<Type *>(Obj)
#define AS_CTYPE(Type, Obj) reinterpret_cast<const Type *>(Obj)

example_context_t *example_new()
{
    return AS_TYPE(example_context_t, new Bank());
}
Bank::Bank() { is_initialized = true; }

void example_free(example_context_t *context)
{
    if (!context)
        return;
    delete AS_TYPE(Bank, context);
}
Bank::~Bank()
{
    is_initialized = false;
    history.clear();
}

void Bank::check_that_context_is_initialized() const
{
    if (not is_initialized)
    {
        fprintf(stderr, "ERROR: context is not initialized\n");
        exit(-1);
    }
}

void example_deposit(example_context_t *context, const double f)
{
    return AS_TYPE(Bank, context)->deposit(f);
}
void example_withdraw(example_context_t *context, const double f)
{
    return AS_TYPE(Bank, context)->deposit(-f);
}
void Bank::deposit(const double f)
{
    check_that_context_is_initialized();
    history.push_back(f);
}

double example_get_balance(const example_context_t *context)
{
    return AS_CTYPE(Bank, context)->get_balance();
}
double Bank::get_balance() const
{
    check_that_context_is_initialized();
    return std::accumulate(history.begin(), history.end(), 0.0);
}

void example_print_history(const example_context_t *context)
{
    return AS_CTYPE(Bank, context)->print_history();
}
void Bank::print_history() const
{
    check_that_context_is_initialized();
    printf("transaction history:\n");
    for (int i = 0; i < history.size(); i++)
    {
        printf("    %f\n", history[i]);
    }
}
