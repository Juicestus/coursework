#include <threading.h>

void t_init()
{
	for (int i = 0; i < NUM_CTX; i++)
	{
		contexts[i].state = INVALID;
	}
	contexts[0].state = VALID;
	current_context_idx = 0;
}

int find_first_empty_context()
{
	for (int i = 1; i < NUM_CTX; i++)
	{
		if (contexts[i].state == INVALID)
			return i;
	}
	return -1;
}

int32_t t_create(fptr foo, int32_t arg1, int32_t arg2)
{
	int idx = find_first_empty_context();
	if (idx == -1)	return 1;	// no context found

	getcontext(&contexts[idx].context);
	char* stack = malloc(STK_SZ);
	if (!stack) return 1; 					// malloc failed -> stack is null

	contexts[idx].context.uc_stack.ss_sp = stack;
	contexts[idx].context.uc_stack.ss_size = STK_SZ;
	contexts[idx].context.uc_stack.ss_flags = 0;
	contexts[idx].context.uc_link = NULL;
	
	// construct the new context	
	makecontext(&contexts[idx].context, (void (*)())foo, 2, arg1, arg2);
	contexts[idx].state = VALID;

	return 0;
}

int find_next_valid_context()
{
	for (int i = 1; i < NUM_CTX; i++)
	{
		int idx = (current_context_idx + i) % NUM_CTX;
		if (contexts[idx].state == VALID)
			return idx;
	}
	return -1;
}

int32_t t_yield()
{
	int idx = find_next_valid_context();
	// this is chill
	if (idx == -1 || idx == current_context_idx) 	return 0;	

	int old_idx = current_context_idx;
	current_context_idx = (uint8_t)idx;	

	swapcontext(&contexts[old_idx].context, &contexts[idx].context);
	
	int nvalid = 0;
	for (int i = 0; i < NUM_CTX; i++)
	{
		if (i == current_context_idx) continue;
		if (contexts[i].state == VALID) nvalid++;
	}
	return nvalid;
}

void t_finish()
{
	int idx = current_context_idx;	
	if (contexts[idx].context.uc_stack.ss_sp != NULL)
		free(contexts[idx].context.uc_stack.ss_sp);

	contexts[idx].state = DONE;
	
	idx = find_next_valid_context();
	if (idx != -1) {}

	current_context_idx = (uint8_t)idx;
	setcontext(&contexts[idx].context);
	
	exit(1);
}
