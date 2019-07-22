#ifndef QUEUE_H
#define QUEUE_H
#include "status.h"

typedef void* QUEUE;

//Init
QUEUE queue_init_default(void);

//enqueue; put into the queue
Status queue_enqueue(QUEUE hQ, int item);

//service; remove from the queue
Status queue_service(QUEUE hQ);

//front
int queue_front(QUEUE hQ, Status* pStatus);

//empty
Boolean queue_empty(QUEUE hQ);

//Print
void queue_print(QUEUE hQ);

//Destroy
void queue_destroy(QUEUE* phQ);

#endif
 
