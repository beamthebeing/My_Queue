#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue
{
    int index_of_front;
    int index_of_entry;
    int size;
    int capacity;
    int* data;
};
typedef struct queue Queue;

QUEUE queue_init_default(void)
{
    Queue* pQ;
    pQ = (Queue*)malloc(sizeof(Queue));
    if (pQ != NULL)
    {
        pQ->size = 0;
        pQ->capacity = 8;
        pQ->index_of_entry = 0;
        pQ->index_of_front = 0;
        pQ->data = malloc(sizeof(int)*pQ->capacity);
        if (pQ->data == NULL)
        {
            free(pQ);
            return NULL;
        }
    }
    return (QUEUE)pQ;
}

Status queue_enqueue(QUEUE hQ, int item)
{
    Queue* pQ = (Queue*)hQ;
    int* pTemp;
    int i;
    int j;
    
    if (pQ->size >= pQ->capacity) //not enough room so resize
    {
        pTemp = malloc(sizeof(int) * pQ->capacity * 2);
        if (pTemp == NULL)
        {
            return FAILURE;
        }
        for (i = 0, j=pQ->index_of_front; i < pQ->size; i++)
        {
            pTemp[i] = pQ->data[j];
            j = (j + 1)%pQ->capacity;
        }
        free(pQ->data);
        pQ->data = pTemp;
        pQ->capacity *= 2;
        pQ->index_of_front = 0;
        pQ->index_of_entry = pQ->size;
    }
    
    pQ->data[pQ->index_of_entry] = item;
    pQ->index_of_entry = (pQ->index_of_entry + 1) % pQ->capacity;
    pQ->size++;
    
    return SUCCESS;
}

Status queue_service(QUEUE hQ)
{
    Queue* pQ = (Queue*)hQ;
    if (queue_empty(hQ))
    {
        return FAILURE;
    }
    pQ->index_of_front = (pQ->index_of_front + 1) % pQ->capacity;
    pQ->size--;
    return SUCCESS;
}

Boolean queue_empty(QUEUE hQ)
{
    Queue* pQ = (Queue*)hQ;
    
    return (Boolean)(pQ->size <= 0);
}

int queue_front(QUEUE hQ, Status* pStatus)
{
    Queue* pQ = (Queue*)hQ;
    if (queue_empty(hQ))
    {
        if (pStatus != NULL)
        {
            *pStatus = FAILURE;
        }
        return -1337;
    }
    
    if (pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
    return pQ->data[pQ->index_of_front];
}

void queue_print(QUEUE hQ)
{
    Queue* pQ = (Queue*) hQ;
    int i;
    
    for(i = pQ->index_of_front; i < pQ->size + pQ->index_of_front; i ++)
    {
        printf("%d:%d\n", i - pQ->index_of_front,  pQ->data[i % pQ->capacity]);
    }
}

void queue_destroy(QUEUE* phQueue)
{
    Queue* pQ = (Queue*)*phQueue;
    free(pQ->data);
    free(pQ);
    *phQueue = NULL;
}
