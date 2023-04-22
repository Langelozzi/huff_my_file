//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef NODE_H
#define NODE_H

/**
 * Node class that represents a Node capable of being used in a priority queue as well as a tree data structure.
 * @author Lucas Angelozzi
 * @version 1.0.0
 */
class Node {
private:
    char data;
    int priority;
    Node *left, *right;

public:
    /**
     * Instantiate a Node without a priority or left or right.
     */
    explicit Node(char newData);

    /**
     * Instantiate a new Node with data and a priority.
     * @param newData the data to store in the Node
     * @param newPriority the priority of the Node in a PriorityQueue
     */
    Node(char newData, int newPriority);

    /**
     * Get the data in the Node.
     * @return the data in the Node
     */
    char getData() const;

    /**
     * Set the data in the Node.
     * @param newData the data to set in the Node
     */
    void setData(char newData);

    /**
     * Get the priority of the Node.
     * @return the Node's priority
     */
    int getPriority() const;

    /**
     * Set the priority of the Node.
     * @param newPriority the updated priority
     */
    void setPriority(int newPriority);

    /**
     * Get a pointer to the left Node.
     * @return a pointer to the left Node
     */
    [[nodiscard]] Node* getLeft() const;

    /**
     * Set the left Node.
     * @param newLeft a pointer to the new left Node
     */
    void setLeft(Node* newLeft);

    /**
     * Get a pointer to the right Node.
     * @return a pointer to the right Node
     */
    [[nodiscard]] Node* getRight() const;

    /**
     * Set the right Node.
     * @param newRight a pointer to the new right Node
     */
    void setRight(Node* newRight);

    /**
     * Determine if this Node is a leaf Node, i.e. has no left or right Nodes.
     * @return a positive integer if it is a leaf node, 0 if it's not
     */
    [[nodiscard]] int isLeaf() const;
};


#endif //NODE_H
