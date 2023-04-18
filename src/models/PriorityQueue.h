//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <unordered_map>
#include "Node.h"

/**
 * PriorityQueue class represents a PriorityQueue data structure containing Nodes.
 * @author Lucas Angelozzi
 * @version 1.0.0
 */
class PriorityQueue {
private:
    std::vector<Node*> queue;

public:
    /**
     * Instantiate a new PriorityQueue constructed from a character frequency map.
     * @param map an unordered_map containing the frequency of characters
     */
    explicit PriorityQueue(const std::unordered_map<char, int>& map);

    /**
     * Get the number of Nodes in the PriorityQueue.
     * @return the number of Nodes in the PriorityQueue
     */
    // [[nodiscard]] lets the user know to assign the value to a variable or use it in some way
    [[nodiscard]] int getSize() const;

    /**
     * Get the vector of Nodes representing the PriorityQueue.
     * @return a vector of Nodes
     */
    [[nodiscard]] std::vector<Node *> getQueue() const;

    /**
     * Insert a Node into the PriorityQueue, placing it in the proper spot based on it's priority.
     * @param node the Node to be added
     */
    void insert(Node* node);

    /**
     * Create and insert a new Node into the PriorityQueue with the given data and priority.
     * @param data the data in the Node
     * @param priority the priority of the Node
     */
    void insert(char data, int priority);

    /**
     * Remove and return the front Node in the PriorityQueue.
     * @return the front Node
     */
    Node* dequeue();

    /**
     * Print the content of the PriorityQueue to stdout.
     */
    void print() const;
};


#endif //PRIORITYQUEUE_H
