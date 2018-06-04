#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "string.h"

static uint32_t nodes_count = 0;
static uint32_t deep_count = 0;

static void count_nodes(const Node_t *root)
{
   Node_t *aux = root->child;

    while(aux != NULL) {
        if (aux->child != NULL) {
            count_nodes(aux);
        } 
        nodes_count++;
        aux = aux->next;
    }
}

static void count_deep(const Node_t *root, uint8_t deep)
{
    Node_t *aux = root->child;

    if (deep_count < deep) {
        deep_count = deep;
    }

    while(aux != NULL) {
        if (aux->child != NULL) {
            count_deep(aux->child, deep + 1);
        } 
        aux = aux->next;
    }
}

static void _delete_node(Node_t *node)
{
    Node_t *aux = node->child;
    Node_t *aux2;
 
    while (aux != NULL) {
        aux2 = aux->next;
        _delete_node(aux);
        aux = aux2;
    }

    free(node);
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

int8_t get_deep_count(Node_t *node)
{
    deep_count = 0;
    count_deep(node, 0);
    return deep_count;
}

retval_t delete_node(Node_t *node)
{
    Node_t *aux, *before;
    
    if (node->parent != NULL) {
        aux = node->parent->child;
        before = NULL;

        while (aux != node) {
            before = aux;
            aux = aux->next;
            
            if (aux == NULL) {
             return RV_ERROR;
            }   
        }

        if (before != NULL) {
            before->next = node->next;
        }else {
            node->parent->child = node->next;
        }
    }

    _delete_node(node);
    return RV_SUCCESS;
}
