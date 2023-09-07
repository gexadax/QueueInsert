#include "QueueInsert.h"

FineGrainedQueue::FineGrainedQueue()
{
    head = nullptr;
    queue_mutex = new std::mutex;
}

FineGrainedQueue::~FineGrainedQueue()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp->node_mutex;
        delete temp;
    }
    delete queue_mutex;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = nullptr;
    new_node->node_mutex = new std::mutex;

    std::unique_lock<std::mutex> queue_lock(*queue_mutex);
        
    Node* current = head;
    Node* previous = nullptr;
    int current_pos = 0;

    while (current_pos < pos - 1 && current != nullptr && current->next != nullptr) {
        previous = current;
        current = current->next;
        current_pos++;
    }

    if (current != nullptr) {
        
        std::unique_lock<std::mutex> current_lock(*current->node_mutex);
        std::mutex* next_mutex = (current->next != nullptr) ? current->next->node_mutex : new std::mutex;
        std::unique_lock<std::mutex> next_lock(*next_mutex);
                
        new_node->next = current->next;
        current->next = new_node;
                
        current_lock.unlock();
        next_lock.unlock();
    }
    else {
        
        new_node->next = head;
        head = new_node;
    }

    queue_lock.unlock();
}
