//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef NODE_H
#define NODE_H


class Node {
private:
    char data;
    int priority;
    Node *left, *right;

public:
    Node(char newData, int newPriority);

    char getData();

    void setData(char newData);

    int getPriority();

    void setPriority(int newPriority);

    [[nodiscard]] Node *getLeft() const;

    void setLeft(Node *newLeft);

    [[nodiscard]] Node *getRight() const;

    void setRight(Node *newRight);

    int isLeaf();
};


#endif //NODE_H
