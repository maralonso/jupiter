#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "string.h"

static uint32_t nodes_count = 0;

static void count_nodes(const Node_t *root)
{
   Node_t *aux = root->child;

    while(aux != NULL) {
        if (aux->child != NULL) {
            count_nodes(aux->child);
        } else {
            nodes_count++;
        }
        aux = aux->next;
    }
}

Node_t* create_node(void)
{
    Node_t *new = (Node_t *) malloc(sizeof(Node_t));

    if (new == NULL) {
        printf("No memory available\n");
    }

    return new;
}

void insert_node(Node_t *parent, Node_t *child)
{
    child->parent = parent;

    if (parent->child == NULL) {
        parent->child = child;
    }
    else {
        Node_t *aux = parent->child;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = child;
    }
}

uint32_t get_tree_count(const Node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    nodes_count = 1;
    count_nodes(root);

   return nodes_count;
}
