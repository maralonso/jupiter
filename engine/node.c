#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "string.h"

static uint32_t nodes_count = 0;
static uint32_t deep_count = 0;
static uint64_t perft_nodes_count = 0;

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

static void _perft(const Node_t *node, uint8_t deep)
{
    if (deep == 0) {
        perft_nodes_count++;
    } else {

        const Node_t *aux = node->child;
        while(aux != NULL) {
            _perft(aux, deep - 1);
            aux = aux->next;
        }
    }
}

static void count_deep(const Node_t *root, uint8_t deep)
{

    if (deep_count < deep) {
        deep_count = deep;
    }

    Node_t *aux = root->child;
    while(aux != NULL) {
        count_deep(aux, deep + 1);
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
    Node_t *new = (Node_t *) calloc(sizeof(Node_t), 1);

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

int8_t get_deep_count(const Node_t *node)
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

uint64_t perft(const Node_t *node)
{
    uint8_t deep = get_deep_count(node);

    perft_nodes_count = 0;
    _perft(node, deep);

    return perft_nodes_count;
}

uint64_t split_perft(const Node_t *node)
{
    uint8_t deep = get_deep_count(node);
    uint64_t total_count = 0;
    Node_t *aux = node->child;
    while (aux != NULL) {
        perft_nodes_count = 0;
        _perft(aux, deep-1);
        printf("%s -- %ld\n", aux->notation, perft_nodes_count);
        total_count = total_count + perft_nodes_count;
        aux = aux->next;
    }

    return total_count;
}
