//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include <iostream>
#include "PriorityQueue.h"
#include "Node.h"

PriorityQueue::PriorityQueue(const std::unordered_map<char, int>& map) {
    for (auto iterator : map) {
        char letter = iterator.first;
        int freq = iterator.second;

        this->insert(letter, freq);
    }
}

int PriorityQueue::getSize() const {
    return this->queue.size();
}

std::vector<Node *> PriorityQueue::getQueue() const {
    return queue;
}

void PriorityQueue::insert(Node *node) {
    if (this->getSize() == 0 || node->getPriority() >= this->getQueue().at(this->getSize() - 1)->getPriority()) {
        this->queue.push_back(node);
        return;
    }

    int index = 0;
    while (node->getPriority() >= this->getQueue().at(index)->getPriority()) {
        index++;
    }

    auto ptr = this->queue.begin();
    std::advance(ptr, index);
    this->queue.insert(ptr, node);
}

void PriorityQueue::insert(char data, int priority) {
    auto* newNode = new Node(data, priority);

    this->insert(newNode);
}

Node* PriorityQueue::dequeue() {
    if (this->getSize() == 0) {
        return nullptr;
    }

    Node* frontNode = this->queue.at(0);
    this->queue.erase(this->queue.begin());

    return frontNode;
}

void PriorityQueue::print() const {
    if (this->getSize() == 0) {
        std::cout << "[]" << std::endl;
    }

    std::cout << "[" << this->getQueue().at(0)->getData();
    for (int i = 1; i < this->getSize(); i++) {
        std::cout << ", " << this->getQueue().at(i)->getData();
    }
    std::cout << "]" << std::endl;
}

