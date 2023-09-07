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
    std::thread thread2(insertThread, std::ref(queue), 200, 6);
    std::thread thread3(insertThread, std::ref(queue), 300, 7);
    std::thread thread4(insertThread, std::ref(queue), 400, 4);
    std::thread thread5(insertThread, std::ref(queue), 500, 8);
    std::thread thread6(insertThread, std::ref(queue), 600, 5);
    std::thread thread7(insertThread, std::ref(queue), 700, 7);
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();

    Node* current = queue.getHead();

    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }

    return 0;
}
