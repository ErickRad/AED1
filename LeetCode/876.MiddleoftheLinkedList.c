#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int data;
    struct ListNode *next;
};

struct ListNode* middleNode(struct ListNode* head){
    int count = 0;
    struct ListNode* current = head;
    while(current != NULL){
        count++;
        current = current->next;
    }
    current = head;
    for(int i = 0; i < count / 2; i++){
        current = current->next;
    }
    return current;
}

int main(){
    struct ListNode node5 = {5, NULL};
    struct ListNode node4 = {4, &node5};
    struct ListNode node3 = {3, &node4};
    struct ListNode node2 = {2, &node3};
    struct ListNode head = {1, &node2};

    struct ListNode* middle = middleNode(&head);

    printf("%d", middle->data);

    return 0;
}
