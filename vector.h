#ifndef CS61C_VECTOR_H_
#define CS61C_VECTOR_H_
#include <sys/types.h>
typedef struct vector_t vector_t;

/* Create a new vector */
vector_t *vector_new();

/* Free up the memory allocated for the passed vector */
void vector_delete(vector_t *v);

/* Return the value in the vector */
int vector_get(vector_t *v, size_t loc);

/* Set a value in the vector */
void vector_set(vector_t *v, size_t loc, int value);

#endif
