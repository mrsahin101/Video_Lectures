#include <stdio.h>

#define BUFFER_SIZE 10

// QUEUE like circular buffer, Insert from tail remove from head.
struct cb
{
    int CB[BUFFER_SIZE];
    int headIndex;
    int tailIndex;
}circularBuffer;

typedef enum __bl
{
    FALSE = 0,
    TRUE = 1,
}bool;

bool checkCBcapacity()
{
    if(circularBuffer.headIndex + circularBuffer.tailIndex == BUFFER_SIZE - 1)
        return TRUE;
    else
        return FALSE;
}
void insertToCB(int data)
{   
    // CB Full
    if(checkCBcapacity() == TRUE)
    {
        if(circularBuffer.tailIndex == BUFFER_SIZE - 1)
        {
            circularBuffer.tailIndex = 0;
            circularBuffer.CB[circularBuffer.tailIndex] = data;
            circularBuffer.headIndex++;
        }
        else
        {
            circularBuffer.CB[circularBuffer.tailIndex++] = data;
            circularBuffer.headIndex++;
        }
    }
    else    // Not full yet
    {
        circularBuffer.CB[circularBuffer.tailIndex--] = data;
    }

}
void removeFromCB()
{

}
void circularBufferInit()
{
    for(int i = 0; i < BUFFER_SIZE; i++)
        circularBuffer.CB[i] = 0x00;
    circularBuffer.headIndex = BUFFER_SIZE - 1;
    circularBuffer.tailIndex = BUFFER_SIZE - 1;
}
void printCB()
{
    if(checkCBcapacity() == TRUE)
    {
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%dth Item : %d\n",i + 1, circularBuffer.CB[circularBuffer.headIndex]);
        }
    }
    else
    {
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%dth Item : %d\n",i + 1, circularBuffer.CB[i]);
        }
    }
}
int main()
{
    circularBufferInit();
    for(int i = 0; i < BUFFER_SIZE; i++)
        insertToCB(5);
    insertToCB(10);
    printCB();   
}