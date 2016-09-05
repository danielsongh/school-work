#include "list.h"

void freeList(node_t ** head)
{
    node_t * temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void printList(node_t * head)
{
    node_t * current = head;

    printf("\nlist: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

node_t * createNode(int val)
{
    node_t * new_node = malloc(sizeof(node_t));

    new_node->data = val;
    new_node->next = NULL;

    return new_node;
}


node_t * insertNode(node_t * head, int val)
{
    if (head == NULL) {
        head = createNode(val);
    }
    else {
        node_t * temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = createNode(val);
    }

    return head;
}

node_t * removeNode(node_t * curr, int val)
{
    
    if (curr == NULL) {
        return NULL;
    }

    if (curr->data == val) {
        node_t * temp = curr->next;

        free(curr);

        return temp;
    }

    curr->next = removeNode(curr->next, val);

    return curr;
}

int searchList(node_t * head, int val)
{
    node_t * temp = head;


    while(temp) {
        if (temp->data == val) {

            return 1;
        } 
        else {
            temp = temp->next;
        }
    }

    return 0;
}