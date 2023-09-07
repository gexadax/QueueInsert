#include <iostream>
#include <thread>
#include "QueueInsert.h"

int main()
{
    // Create a FineGrainedQueue instance.
    FineGrainedQueue queue;

    // Insert values from 0 to 9 into the middle of the queue.
    for (int i = 0; i < 10; i++)
    {
        queue.insertIntoMiddle(i, i);
    }

    // Create a vector of threads to simulate concurrent insertions.
    std::vector<std::thread> threads;
    threads.reserve(7);

    // Spawn seven threads to insert values into the middle of the queue concurrently.
    for (int i = 0; i < 7; i++) {
        threads.emplace_back([&queue, i]() {
            queue.insertIntoMiddle(100 * (i + 1), 5 + i);
            });
    }

    // Join all the threads to wait for them to complete.
    for (auto& thread : threads) {
        thread.join();
    }

    // Retrieve the head of the queue.
    Node* current = queue.getHead();

    // Print the values in the queue.
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }

    return 0;
}
