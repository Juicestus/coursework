#include <threading.h>

/**
 * This vector holds all the stored contexts
 */
struct worker_context contexts[NUM_CTX];

/**
 * The index to the current context
 */
uint8_t current_context_idx = NUM_CTX; // Initialize to garbage
