#ifndef LIST_H
#define LIST_H

typedef struct Node{
    char *data;
    struct Node *next;

}Node;

int createNode(char *data);
void printNodes();
void clean();

#endif