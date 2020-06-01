#ifndef __NODE__H
#define __NODE__H

#include "board.h"

Node_t* create_node(void);
void insert_node(Node_t *parent, Node_t *child);
retval_t delete_node(Node_t *node);
uint32_t get_tree_count(const Node_t *root);
uint64_t perft(const Node_t *node);
uint64_t split_perft(const Node_t *node);
int8_t get_deep_count(const Node_t *node);

#endif
