#include <iostream>
#include <thread>
#include "QueueInsert.h"

void insertThread(FineGrainedQueue& queue, int value, int pos)
{
    queue.insertIntoMiddle(value, pos);
}

int main()
{
    FineGrainedQueue queue;

   
    for (int i = 0; i < 10; i++)
    {
        queue.insertIntoMiddle(i, i);
    }

   
    std::thread thread1(insertThread, std::ref(queue), 100, 5);
    std::thread thread2(insertThread, std::ref(queue), 200, 7);

 
    thread1.join();
    thread2.join();

 
    Node* current = queue.getHead();
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }

    return 0;
}
