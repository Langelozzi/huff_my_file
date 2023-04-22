//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include "Node.h"

Node::Node(char newData) {
    this->data = newData;
    this->priority = 0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(char newData, int newPriority) {
    this->data = newData;
    this->priority = newPriority;
    this->left = nullptr;
    this->right = nullptr;
}

char Node::getData() const {
    return this->data;
}

void Node::setData(char newData) {
    this->data = newData;
}

int Node::getPriority() const {
    return this->priority;
}

void Node::setPriority(int newPriority) {
    this->priority = newPriority;
}

Node* Node::getLeft() const {
    return this->left;
}

void Node::setLeft(Node *newLeft) {
    this->left = newLeft;
}

Node* Node::getRight() const {
    return this->right;
}

void Node::setRight(Node *newRight) {
    Node::right = newRight;
}

int Node::isLeaf() const {
    return !(this->getLeft()) && !(this->getRight());
}