//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <unordered_map>
#include "Node.h"

class PriorityQueue {
private:
    std::vector<Node*> queue;

public:
    explicit PriorityQueue(const std::unordered_map<char, int>& map);
    // [[nodiscard]] lets the user know to assign the value to a variable or use it in some way
    [[nodiscard]] int getSize() const;

    [[nodiscard]] const std::vector<Node *> &getQueue() const;

    void insert(Node* node);

    void insert(char data, int priority);

    Node* dequeue();

    void print() const;
};


#endif //PRIORITYQUEUE_H
