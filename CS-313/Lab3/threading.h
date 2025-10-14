#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

#ifndef COOPERATIVE_MULTITASKING
#define COOPERATIVE_MULTITASKING

#define STK_SZ  4096
#define NUM_CTX 16

/**
 * This enum describes the various states an instance of stored context can be
 * in
 */
enum context_state
{
        INVALID = 0, // The context entry is invalid
        VALID   = 1, // The context entry is valid and ready to be used
        DONE    = 2, // This context has completed its work
};

/**
 * This structure holds the metadata necessary for context switches
 */
struct worker_context
{
        /**
         * By default entries are in INVALID state since they haven't been
         * initialized yet. The initialization is supposed to be done by
         * t_init()
         */
        enum context_state state;

        /**
         * The actual context
         */
        ucontext_t context;
};

/**
 * The list of contexts and the index to the current context. Note that these
 * are declared in threading_data.c
 */
extern struct worker_context contexts[NUM_CTX];
extern uint8_t               current_context_idx;

typedef void (*fptr)(int32_t, int32_t);
typedef void (*ctx_ptr)(void);

/**
 * This function initializes the various data structures necessary for
 * cooperative multitasking
 */
void t_init();

/**
 * This function takes in a lambda function and the arguments to be passed to
 * the lambda. It then creates a context out of these two pieces of data and
 * stores it in the contexts list
 *
 * param foo: A function pointer of the type fptr to the lambda
 * param arg1: The first argument to be passed to foo
 * param arg2: The second argument to be passed to foo
 * returns: 0 if successful, 1 otherwise
 */
int32_t t_create(fptr foo, int32_t arg1, int32_t arg2);

/**
 * This function cooperatively yields the control over to other workers. This
 * function may or may not return in the caller
 *
 * returns: This function returns the number of contexts (apart from the
 *          caller) which are in the VALID state if it is successful, otherwise
 *          it returns -1
 */
int32_t t_yield();

/**
 * This function is called by the worker to indicate that it has completed its
 * work. After this function is called, the worker's context is deleted and the
 * worker is never scheduled back again 
 */
void t_finish();

#endif
