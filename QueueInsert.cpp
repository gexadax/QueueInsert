#include "QueueInsert.h"

FineGrainedQueue::FineGrainedQueue()
{
    head = nullptr;
}

FineGrainedQueue::~FineGrainedQueue()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = nullptr;
    new_node->node_mutex = std::make_unique<std::mutex>();

    {
        std::lock_guard<std::mutex> queue_lock(queue_mutex);

        Node* current = head;
        Node* previous = nullptr;
        int current_pos = 0;

        while (current_pos < pos - 1 && current != nullptr) {
            previous = current;
            current = current->next;
            current_pos++;
        }

        if (previous != nullptr) {
            std::unique_lock<std::mutex> current_lock(*(previous->node_mutex));
            std::unique_lock<std::mutex> next_lock(*(new_node->node_mutex));

            new_node->next = previous->next;
            previous->next = new_node;
        }
        else {
            std::unique_lock<std::mutex> next_lock(*(new_node->node_mutex));
            new_node->next = head;
            head = new_node;
        }
    }
}
