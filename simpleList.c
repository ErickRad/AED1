#include "simpleList.h"
#include <stdlib.h>
#include <stdio.h>

Node *head = NULL;

int createNode(char *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) return 0;

    node->data = data;
    node->next = NULL;

    if (head == NULL) {
        head = node;

    } else {
            Node *current = head;
            while(current-> next != NULL){
                current = current->next;
            }
            current->next = node;
    }
    return 1;
}

void printNodes(){
    if(head != NULL){
        Node *current = head;

        while(current != NULL) {
            if(current->next != NULL){
                printf("%s -> ", current->data);
            }else{
                printf("%s", current->data);
            }
            current = current->next;        
        }
        printf("\n");
    }
}

void clean() {
    Node *current = head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(){
    createNode("One");
    createNode("Two");
    createNode("Three");
    createNode("Four");

    printNodes();

    clean();
}

